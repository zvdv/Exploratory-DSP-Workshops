/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "i2s.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "CS43L22.h"
#include <math.h>
#include "arm_math.h"
#include <stdio.h>
#include <stdlib.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define N	1024
#define FILTER_NUM_COEFFS 61
#define TALK_THROUGH 1
#define FIR_FILTER 0
#define CALC_FFT 0
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint32_t adc_val[2*N];
uint16_t count;

float32_t input_buffer[2*N];	// CMSIS DSP library requires float values
float32_t output_buffer[2*N];
float32_t *input_buffer_ptr;
float32_t *output_buffer_ptr;

uint16_t audio_buffer_out[4*N];

arm_fir_instance_f32 lpfilter;
float32_t state[FILTER_NUM_COEFFS + N -1];

uint8_t adc_callback_state = 0;
uint8_t i2s_callback_state = 0;

// 61 filter coefficients Matlab b=fir1(60,0.125);
// cutoff frequency approximately 2.9 kHz for 48 kHz sampling

const float32_t filter_coeffs[FILTER_NUM_COEFFS] = {
		-0.000602, -0.000839, -0.001026, -0.001119, -0.001039,
		-0.000692, 0.000000, 0.001052, 0.002381, 0.003785,
		0.004946, 0.005475, 0.004987, 0.003192, -0.000000,
		-0.004396, -0.009477, -0.014414, -0.018138, -0.019485,
		-0.017373, -0.010995, 0.000000, 0.015383, 0.034300,
		0.055324, 0.076597, 0.096050, 0.111676, 0.121797,
		0.125301, 0.121797, 0.111676, 0.096050, 0.076597,
		0.055324, 0.034300, 0.015383, 0.000000, -0.010995,
		-0.017373, -0.019485, -0.018138, -0.014414, -0.009477,
		-0.004396, -0.000000, 0.003192, 0.004987, 0.005475,
		0.004946, 0.003785, 0.002381, 0.001052, 0.000000,
		-0.000692, -0.001039, -0.001119, -0.001026, -0.000839,
		-0.000602
};

arm_rfft_fast_instance_f32 fft;
float32_t mag[N];
float32_t fft_out[2*N];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
int __io_putchar(int ch);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void process_DSP(){
	#if TALK_THROUGH
		for(int i = 0; i < N; i++){
			*(output_buffer_ptr + i)= *(input_buffer_ptr + i);
		}

	#elif FIR_FILTER
		arm_fir_f32(&lpfilter, input_buffer_ptr, output_buffer_ptr, N);

	#elif CALC_FFT
		for(int i = 0; i < N; i++){
			*(output_buffer_ptr + i)= *(input_buffer_ptr + i);
		}
		arm_rfft_fast_f32(&fft, input_buffer_ptr, fft_out, 0);
		// https://arm-software.github.io/CMSIS-DSP/main/group__RealFFT.html
		// first two elements of fft_out are X[0] and X[N/2], both purely real
		mag[0] = fft_out[0];
		mag[N/2] = fft_out[1];
		// the remainder of fft_out are pairs of real and imaginary
		for(int i=1; i < N/2; i++){
			mag[i] = sqrt(pow(fft_out[2*i],2) + pow(fft_out[2*i+1],2));
		}


	#endif
}

void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc)
{
//	// first half of buffer is full
	adc_callback_state = 1;

}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	// second half of buffer is full
	adc_callback_state = 2;

}

void HAL_I2S_TxHalfCpltCallback(I2S_HandleTypeDef *hi2s)
{
	i2s_callback_state = 1;

}

void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef *hi2s)
{
	i2s_callback_state = 2;

}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM2_Init();
  MX_ADC1_Init();
  MX_I2C1_Init();
  MX_I2S3_Init();
  /* USER CODE BEGIN 2 */
  CS43_Init(hi2c1, MODE_I2S);
  CS43_SetVolume(40); // 0 - 40
  CS43_Enable_RightLeft(CS43_RIGHT_LEFT);
  CS43_Start();

  arm_fir_init_f32(&lpfilter, FILTER_NUM_COEFFS, &filter_coeffs[0], &state[0], N);
  arm_rfft_fast_init_f32(&fft, N);

  HAL_TIM_Base_Start(&htim2);
  HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc_val, 2*N);
  HAL_I2S_Transmit_DMA(&hi2s3, (uint16_t *) audio_buffer_out, 4*N);



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if(adc_callback_state != 0){
		  if (adc_callback_state == 1) { //buffer half full
			  for(int i = 0; i < N; i++){
	  			  input_buffer[i] = (float32_t) adc_val[i];
			  }

			  input_buffer_ptr = &input_buffer[0];
			  output_buffer_ptr = &output_buffer[0];

		  }
		  else if (adc_callback_state == 2) { //buffer full
			  for(int i = N; i < 2*N; i++){
				  input_buffer[i]= (float32_t) adc_val[i];
			  }

			  input_buffer_ptr = &input_buffer[N];
	  		  output_buffer_ptr = &output_buffer[N];

		  }
		  process_DSP();
	  	  adc_callback_state = 0;

	  }

  	  if(i2s_callback_state != 0){
  		  if(i2s_callback_state == 1){

  	  		  for(int i = 0; i < N; i++){
  	  		  		audio_buffer_out[2*i] = (uint16_t) output_buffer[i];
  	  		  		audio_buffer_out[2*i+1] = (uint16_t) output_buffer[i];
  	  		  }
  		  }
  		  else if(i2s_callback_state == 2) {

  	  		  for(int i = N; i < 2*N; i++){
  	  		  		audio_buffer_out[2*i] = (uint16_t) output_buffer[i];
  	  		  		audio_buffer_out[2*i+1] = (uint16_t) output_buffer[i];
  	  		  	}
  		  }
  		  i2s_callback_state = 0;

  	  }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
int __io_putchar(int ch){
	ITM_SendChar(ch);
	return 0;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
