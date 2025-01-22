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
#include <stdio.h>
#include <stdlib.h>

#include "aweCore.h"
#include "AWECoreUtils.h"
#include "STM32F407_PassThru_with_ControlIO.h"
#include "reverb_with_mux_ControlInterface.h"
#include "reverb_with_mux_InitAWB.h"
#include "platform_awe.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define N	AUDIO_BLOCK_SIZE

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint32_t adc_val[2*N];
uint16_t count;

float input_buffer[2*N];
float output_buffer[2*N];
float *input_buffer_ptr;
float *output_buffer_ptr;

uint16_t audio_buffer_out[4*N];
fract16 send_to_AWE_buffer[4*N];
INT16 receive_from_AWE_buffer[4*N];

volatile uint8_t adc_callback_state = 0;
volatile uint8_t i2s_callback_state = 0;

/** this AWE instance */
AWEInstance g_AWEInstance;

volatile BOOL g_bBlinkLED4ForBoardAlive = TRUE;

INT32 nLoopCount = 0;

// variable types are indicated in reverb_mux_ControlInterface.h
int user_button = 1;
int delay1Value = 2000;
float scaler1Gain = -3.0;

ADC_ChannelConfTypeDef sConfig2 = {0};
ADC_ChannelConfTypeDef sConfig3 = {0};

UINT32 potValue=0;
UINT32 potValue2=0;

float tot = 0.0;
float tot2 = 0.0;
int num = 0;
int num2 = 0;

UINT32 nErrorOffset;
INT32 nResult;

UINT32 classID;
INT32 nButtonState, nLED1State;

INT32 bAudioIsStarted;
INT32 bLayoutValid;

//uint32_t aa, bb, cc;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
int __io_putchar(int ch);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc)
{
	// first half of ADC buffer is full
	adc_callback_state = 1;
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	// second half of ADC buffer is full
	adc_callback_state = 2;
}

void HAL_I2S_TxHalfCpltCallback(I2S_HandleTypeDef *hi2s)
{
	// first half of I2S buffer full
	i2s_callback_state = 1;
}

void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef *hi2s)
{
	// second half of I2S buffer full
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
  MX_ADC2_Init();
  /* USER CODE BEGIN 2 */
  AWEInstanceInit();
  CS43_Init(hi2c1, MODE_I2S);
  CS43_SetVolume(40); // 0 - 40
  CS43_Enable_RightLeft(CS43_RIGHT_LEFT);
  CS43_Start();

  HAL_TIM_Base_Start(&htim2);
  HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc_val, 2*N);
  HAL_I2S_Transmit_DMA(&hi2s3, (uint16_t *) audio_buffer_out, 4*N);

  nResult = awe_loadAWBfromArray(&g_AWEInstance, Instance0_InitCommands, Instance0_InitCommands_Len, &nErrorOffset);
  if (nResult != E_SUCCESS)
  {
      printf("awe_loadAWBfromArray failed\n");
  }
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
      if (g_bBlinkLED4ForBoardAlive)
      {

          nLoopCount++;

          // total ADC inputs from a pot for averaging to get Scaler1 setting
          // this pot connected to pin PC1 (see adc.c)
          if(nLoopCount >= 1000 && nLoopCount < 1200) {
          	HAL_ADC_ConfigChannel(&hadc2, &sConfig2);
            HAL_ADC_Start(&hadc2);
          	HAL_ADC_PollForConversion(&hadc2,50); //Timeout is 50 msec
          	tot += HAL_ADC_GetValue(&hadc2);
          	num++;
          }

          // total ADC inputs from a second pot for averaging to get Delay1 setting
          // this pot connect to pin PC2 (see adc.c)
          if(nLoopCount >= 2000 && nLoopCount < 2200) {
          	HAL_ADC_ConfigChannel(&hadc2, &sConfig3);
            HAL_ADC_Start(&hadc2);
            HAL_ADC_PollForConversion(&hadc2,50); //Timeout is 50 msec
          	tot2 += HAL_ADC_GetValue(&hadc2);
          	num2++;
          }

          // compute averaged ADC input values
          if (nLoopCount == 62200) //at 168E6 MHz, this count equals approx 1 sec
          {
        	  potValue = (UINT32)(tot/num);
        	  potValue2 = (UINT32)(tot2/num2);
              // Indicate board running by toggling LED4
              HAL_GPIO_TogglePin(Orange_LED_GPIO_Port, Orange_LED_Pin);

              nLoopCount = 0;
              tot = 0.0;
              tot2 = 0.0;
              num = 0;
              num2 = 0;
          }
      }

      if (awe_ctrlGetModuleClass(&g_AWEInstance, AWE_Scaler1_gain_HANDLE, &classID) == OBJECT_FOUND)
      {
        // Check that module assigned this object ID is of module class Scaler1
      	if (classID == AWE_Scaler1_classID)
      	{
      		// convert ADC value to a scaler1Gain in dB between -24 and 24 as per ControlInterface.h
//            scaler1Gain=potValue/2400.0*48.0-24.0;
//            if(scaler1Gain < -24.0) scaler1Gain = -24.0;
//            if(scaler1Gain > 24.0) scaler1Gain = 24.0;
     		scaler1Gain = -3.0;
      		awe_ctrlSetValue(&g_AWEInstance, AWE_Scaler1_gain_HANDLE, (void *)&scaler1Gain, 0, 1);
      	}
      }

      if (awe_ctrlGetModuleClass(&g_AWEInstance, AWE_Delay1_currentDelay_HANDLE, &classID) == OBJECT_FOUND)
      {
        // Check that module assigned this object ID is of module class SinkInt
        if (classID == AWE_Delay1_classID)
        {
           // convert ADC value to a Delay1Value between 0 and 3000  per ControlInterface.h
//           delay1Value=(int)(potValue2/2400.0*3000.0);
//           if(delay1Value < 0) delay1Value = 0;
//           if(delay1Value > 3000) delay1Value = 3000;
          delay1Value = 2900;
          awe_ctrlSetValue(&g_AWEInstance, AWE_Delay1_currentDelay_HANDLE, (void *)&delay1Value, 0, 1);
        }
      }

      if (awe_ctrlGetModuleClass(&g_AWEInstance, AWE_Multiplexor1_index_HANDLE, &classID) == OBJECT_FOUND)
      {
      	// Check that module assigned this object ID is of module class SinkInt
      	if (classID == AWE_Multiplexor1_classID)
      	{
      	   // use this method to provide momentary change to no reverb
      	   // pushed button = 1, unpushed button = 0
           if(HAL_GPIO_ReadPin(UserButton_GPIO_Port, UserButton_Pin)==GPIO_PIN_SET)
           {
           	  user_button = 1;
           }
           else
           {
              user_button = 0;
           }
    	   awe_ctrlSetValue(&g_AWEInstance, AWE_Multiplexor1_index_HANDLE, (void *)&user_button, 0, 1);
      	}
      }

	  if(adc_callback_state != 0){
		  if (adc_callback_state == 1) { //buffer half full
			  for(int i = 0; i < N; i++){
	  			  input_buffer[i] = (float) adc_val[i];
	  			  // send ADC input value
				  send_to_AWE_buffer[2*i] = (fract16)input_buffer[i];
				  send_to_AWE_buffer[2*i+1] = (fract16)input_buffer[i];
			  }

		  }
		  else if (adc_callback_state == 2) { //buffer full
			  for(int i = N; i < 2*N; i++){
				  input_buffer[i]= (float) adc_val[i];
				  send_to_AWE_buffer[2*i] = (fract16) input_buffer[i];
				  send_to_AWE_buffer[2*i+1] = (fract16) input_buffer[i];
			  }

		  }
		  adc_callback_state = 0;
	  }

  	  if(i2s_callback_state != 0){
  	 	  if(i2s_callback_state == 1){

			  bAudioIsStarted = awe_audioIsStarted(&g_AWEInstance);
			  bLayoutValid = awe_layoutIsValid(&g_AWEInstance);

			  if(bAudioIsStarted && bLayoutValid) {
				  // left and right stereo
				  awe_audioImportSamples(&g_AWEInstance, (fract16 *) &send_to_AWE_buffer[0], STRIDE2, CHANNEL1, Sample16bit);
				  awe_audioImportSamples(&g_AWEInstance, (fract16 *) &send_to_AWE_buffer[1], STRIDE2, CHANNEL2, Sample16bit);

				  // pump inputs into AWE layout
				  awe_audioPump(&g_AWEInstance, 0);

				  // left and right stereo
				  awe_audioExportSamples(&g_AWEInstance,  (INT16 *) &receive_from_AWE_buffer[0], STRIDE2, CHANNEL1, Sample16bit);
				  awe_audioExportSamples(&g_AWEInstance,  (INT16 *) &receive_from_AWE_buffer[1], STRIDE2, CHANNEL2, Sample16bit);
			  }

  	  		  for(int i = 0; i < N; i++){
  	  			// left and right stereo
  	  		  	audio_buffer_out[2*i] = (uint16_t) receive_from_AWE_buffer[2*i];
  	  		  	audio_buffer_out[2*i+1] = (uint16_t) receive_from_AWE_buffer[2*i+1];
  	  		  }

  		  }
  	  	  else if(i2s_callback_state == 2) {

			  bAudioIsStarted = awe_audioIsStarted(&g_AWEInstance);
			  bLayoutValid = awe_layoutIsValid(&g_AWEInstance);

			  if(bAudioIsStarted && bLayoutValid) {
				  awe_audioImportSamples(&g_AWEInstance, (fract16 *) &send_to_AWE_buffer[2*AUDIO_BLOCK_SIZE], STRIDE2, CHANNEL1, Sample16bit);
				  awe_audioImportSamples(&g_AWEInstance, (fract16 *) &send_to_AWE_buffer[2*AUDIO_BLOCK_SIZE+1], STRIDE2, CHANNEL2, Sample16bit);

				  awe_audioPump(&g_AWEInstance, 0);

				  awe_audioExportSamples(&g_AWEInstance,  (INT16 *) &receive_from_AWE_buffer[2*AUDIO_BLOCK_SIZE], STRIDE2, CHANNEL1, Sample16bit);
				  awe_audioExportSamples(&g_AWEInstance,  (INT16 *) &receive_from_AWE_buffer[2*AUDIO_BLOCK_SIZE+1], STRIDE2, CHANNEL2, Sample16bit);
			  }

  	  		  for(int i = N; i < 2*N; i++){
  	  		  		audio_buffer_out[2*i] = (uint16_t) receive_from_AWE_buffer[2*i];
  	  		  		audio_buffer_out[2*i+1] = (uint16_t) receive_from_AWE_buffer[2*i+1];
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
