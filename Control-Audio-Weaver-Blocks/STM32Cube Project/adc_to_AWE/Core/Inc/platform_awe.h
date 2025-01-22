/*******************************************************************************
*
*               Audio Framework
*               ---------------
*
********************************************************************************
*     AWE_Wrapper.h
********************************************************************************
*
*     Description:  AudioWeaver Wrapper Header File
*
*     Copyright:    (c) 2018 DSP Concepts, Inc. All rights reserved.
*                   3235 Kifer Road
*                   Santa Clara, CA 95054
*
*******************************************************************************/

#include "aweCore.h"
#include "AWECoreUtils.h"
#include "TargetInfo.h"
#include "Errors.h"
#include <stdio.h>

#include "dspc_asrc_48000_to_48000_32m_080db.h"

/** Create handle. */
#define CREATE_OBJECT_HANDLE(isArray, isFloat, objectID, index) \
	( ((isArray & 1) << 31) | ((isFloat & 1) << 30) | ((objectID & 0x3FFFF) << 12) | (index & 0xFF) )

#if ENABLE_MIC
    #define INPUT_CHANNEL_COUNT 3
#else
    #define INPUT_CHANNEL_COUNT 2
#endif

#define OUTPUT_CHANNEL_COUNT 2
//
//#define MONO_CHANNEL_COUNT 1
//#define STEREO_CHANNEL_COUNT 2

//#define TOTAL_BUFFERS 2
//#define CHANNEL_BLOCK_SIZE_IN_SAMPLES AUDIO_BLOCK_SIZE
//#define STEREO_BLOCK_SIZE_IN_SAMPLES (AUDIO_BLOCK_SIZE * STEREO_CHANNEL_COUNT)
//#define PCM_SIZE_IN_BYTES 2
//
//#define USB_PLAYBACK_BLOCKSIZE 48
//#define MIC_INPUT_BLOCKSIZE 48
//#define CODEC_OUTPUT_BLOCKSIZE AUDIO_BLOCK_SIZE
//
//#define CODEC_BUFFER_SIZE_IN_SAMPLES (STEREO_BLOCK_SIZE_IN_SAMPLES * TOTAL_BUFFERS)
//#define PCM_BUFFER_SIZE_IN_SAMPLES (MIC_INPUT_BLOCKSIZE * TOTAL_BUFFERS)

//#define AWE_COMMAND_BUFFER_LEN 264

// 48000/1000 * 64/8 = 384 (384 / 8 = 48)
//#define PDM_BUFFER_SIZE 384
//#define NEW_PDM_SAMPLES 192

//#define PCM_SAMPLE_SIZE_IN_BYTES 2
//#define PCM_SAMPLE_SIZE_IN_BITS 16



#define FAILURE 0
#define SUCCESS 1

#define STRIDE1 1
#define STRIDE2 2
#define CHANNEL1 0
#define CHANNEL2 1
#define CHANNEL3 2

extern volatile BOOL g_bBlinkLED4ForBoardAlive;

extern I2S_HandleTypeDef hI2S2;
extern I2S_HandleTypeDef hI2S3;

extern volatile unsigned int *DWT_CYCCNT;

//extern DSPC_ASRC USB_ASRC;

extern AWEInstance g_AWEInstance;

// Local method forUserFunction module
extern INT32 (*g_UserSelectFunction)(INT32 nFunctionID, float fSampleRate,
                                     UINT32 * pInput, INT32 nInBlockSize, INT32 nInChannelCnt, INT32 nInDataType, BOOL bInComplex,
                                     UINT32 * pOutput, INT32 nOutBlockSize, INT32 nOutChannelCnt, INT32 nOutDataType, BOOL bOutComplex);

INT32 UserSelectFunction(INT32 nFunctionID, float fSampleRate,
                         UINT32 * pInput, INT32 nInBlockSize, INT32 nInChannelCnt, INT32 nInDataType, BOOL bInComplex,
                         UINT32 * pOutput, INT32 nOutBlockSize, INT32 nOutChannelCnt, INT32 nOutDataType, BOOL bOutComplex);
						 
#define OBJECT_FOUND 0

void awe_pltGPIOSetPinDir(UINT32 nPinNo, UINT32 nPinDir);
void awe_pltGPIOSetPin(UINT32 nPinNo, UINT32 nValue);
void awe_pltGPIOTogglePin(UINT32 nPinNo);
void awe_pltGPIOGetPin(UINT32 nPinNo, UINT32 * nValue);

void awe_vecScaleSmoothFract32(
		     fract32 *              src,
		     int                    srcInc,
		     fract32 *              dst,
		     int                    dstInc,
		     fract32 * VEC_RESTRICT currentGainFract,
		     fract32                targetGainFract,
		     int                    postShift,
		     fract32                smoothingCoeff,
		     int                    blockSize);

//extern volatile fract32 g_nNewVolGain;

#if (HAS_FLASH_FILESYSTEM == 1)

BOOL usrInitFlashFileSystem(void);
INT32 usrGetFlashEraseTime(void);
BOOL usrReadFlashMemory(UINT32 nFlashAddress, UINT32 * pBuffer, UINT32 nDWordsToRead);
BOOL usrWriteFlashMemory(UINT32 nFlashAddress, UINT32 * pBuffer, UINT32 nDWordsToWrite);
BOOL usrEraseFlashMemorySector(UINT32 nStartingAddress, UINT32 nNumberOfSectors);

#define ADDR_FLASH_SECTOR_0     ((UINT32)0x08000000) // Base @ of Sector 0, 16 Kbytes
#define ADDR_FLASH_SECTOR_1     ((UINT32)0x08004000) // Base @ of Sector 1, 16 Kbytes
#define ADDR_FLASH_SECTOR_2     ((UINT32)0x08008000) // Base @ of Sector 2, 16 Kbytes
#define ADDR_FLASH_SECTOR_3     ((UINT32)0x0800C000) // Base @ of Sector 3, 16 Kbytes
#define ADDR_FLASH_SECTOR_4     ((UINT32)0x08010000) // Base @ of Sector 4, 64 Kbytes
#define ADDR_FLASH_SECTOR_5     ((UINT32)0x08020000) // Base @ of Sector 5, 128 Kbytes
#define ADDR_FLASH_SECTOR_6     ((UINT32)0x08040000) // Base @ of Sector 6, 128 Kbytes
#define ADDR_FLASH_SECTOR_7     ((UINT32)0x08060000) // Base @ of Sector 7, 128 Kbytes
#define ADDR_FLASH_SECTOR_8     ((UINT32)0x08080000) // Base @ of Sector 8, 128 Kbytes
#define ADDR_FLASH_SECTOR_9     ((UINT32)0x080A0000) // Base @ of Sector 9, 128 Kbytes
#define ADDR_FLASH_SECTOR_10    ((UINT32)0x080C0000) // Base @ of Sector 10, 128 Kbytes
#define ADDR_FLASH_SECTOR_11    ((UINT32)0x080E0000) // Base @ of Sector 11, 128 Kbytes

#endif

extern AWEFlashFSInstance g_AWEFlashFSInstance;

/** The only input pin for this core. */
extern IOPinDescriptor s_InputPin;

/** The only output pin for this core. */
extern IOPinDescriptor s_OutputPin;
extern  UINT32 g_fastB_heap[FASTB_HEAP_SIZE];
extern UINT32 g_fastA_heap[FASTA_HEAP_SIZE];
extern UINT32 g_slow_heap[SLOW_HEAP_SIZE];

extern const void *g_module_descriptor_table[];
extern UINT32 g_module_descriptor_table_size;

extern volatile unsigned int *DWT_CYCCNT;// 0xE0001004; //address of the register
extern volatile unsigned int *DWT_CONTROL;// 0xE0001000; //address of the register
extern volatile unsigned int *SCB_DEMCR; //0xE000EDFC; //address of the register
extern volatile unsigned int *LAR; //0xE0001FB0; // <-- added lock access register

extern UINT32 g_packet_buffer[MAX_COMMAND_BUFFER_LEN];

void AWEInstanceInit();
void InitCycleCounter(void);
UINT32 aweuser_getCycleCount(void);
UINT32 aweuser_getElapsedCycles(UINT32 nStartTime, UINT32 nEndTime);
BOOL usrInitFlashFileSystem(void);
BOOL usrReadFlashMemory(UINT32 nFlashAddress, UINT32 * pBuffer, UINT32 nDWordsToRead);
BOOL usrWriteFlashMemory(UINT32 nFlashAddress, UINT32 * pBuffer, UINT32 nDWordsToWrite);
BOOL usrEraseFlashMemorySector(UINT32 nStartingAddress, UINT32 nNumberOfSectors);

void awe_pltGPIOSetPinDir(UINT32 nPinNo, UINT32 nPinDir);
void awe_pltGPIOTogglePin(UINT32 nPinNo);
void awe_pltGPIOSetPin(UINT32 nPinNo, UINT32 nValue);
void awe_pltGPIOGetPin(UINT32 nPinNo, UINT32 * nValue);






