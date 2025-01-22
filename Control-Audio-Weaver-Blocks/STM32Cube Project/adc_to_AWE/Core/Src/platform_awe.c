/*
 * platform_awe.c
 *
 *  Created on: Jul 21, 2024
 *      Author: C0000740
 */
/** Flash file system instance */

#include "i2s.h"
#include "platform_awe.h"
#include "PinDef.h"

AWEFlashFSInstance g_AWEFlashFSInstance;

/** The only input pin for this core. */
IOPinDescriptor s_InputPin = { 0 };

/** The only output pin for this core. */
IOPinDescriptor s_OutputPin = { 0 };

#if defined( __ICCARM__ )
    #pragma data_alignment=4
    UINT32 g_fastA_heap[FASTA_HEAP_SIZE];

    #pragma data_alignment=4
	UINT32 g_fastB_heap[FASTB_HEAP_SIZE] @ ".CCMRAM_Section";

    #pragma data_alignment=4
    UINT32 g_slow_heap[SLOW_HEAP_SIZE];
#else
	#if defined( __GNUC__ )
		__attribute__((__section__(".ccmram")))
	#else
        #if defined ( __CC_ARM )
		__attribute__((__section__(".data_CCMRAM")))
        #endif
	#endif
    __ALIGN_BEGIN UINT32 g_fastB_heap[FASTB_HEAP_SIZE] __ALIGN_END;
    __ALIGN_BEGIN UINT32 g_fastA_heap[FASTA_HEAP_SIZE] __ALIGN_END;
    __ALIGN_BEGIN UINT32 g_slow_heap[SLOW_HEAP_SIZE] __ALIGN_END;
#endif

/* ----------------------------------------------------------------------
** Module table
** ------------------------------------------------------------------- */
/* Array of pointers to module descriptors. This is initialized at compile time.
   Each item is the address of a module descriptor that we need linked in. The
   linker magic is such that only those modules referenced here will be in the
   final program. */
const void *g_module_descriptor_table[] =
{
	// The suitably cast pointers to the module descriptors.
   (void *)LISTOFCLASSOBJECTS
};

AWE_MOD_SLOW_DM_DATA UINT32 g_module_descriptor_table_size = sizeof(g_module_descriptor_table) / sizeof(g_module_descriptor_table[0]);

volatile unsigned int *DWT_CYCCNT  = (volatile unsigned int *)(DWT_BASE +  0x004UL) ;// 0xE0001004; //address of the register
volatile unsigned int *DWT_CONTROL = (volatile unsigned int *)(DWT_BASE);// 0xE0001000; //address of the register
volatile unsigned int *SCB_DEMCR   = (volatile unsigned int *)(CoreDebug_BASE + 0x00CUL ) ; //0xE000EDFC; //address of the register
volatile unsigned int *LAR         = (volatile unsigned int *)(DWT_BASE + 0x0FB0UL ) ; //0xE0001FB0; // <-- added lock access register

UINT32 g_packet_buffer[MAX_COMMAND_BUFFER_LEN] = {0};

//-----------------------------------------------------------------------------
// METHOD:  AWEInstanceInit
// PURPOSE: Initialize AWE Instance with target details
//-----------------------------------------------------------------------------
void AWEInstanceInit()
{

	int ret;

    memset(&g_AWEInstance, 0, sizeof(AWEInstance) );

    g_AWEInstance.pInputPin = &s_InputPin;
    g_AWEInstance.pOutputPin = &s_OutputPin;

    ret = awe_initPin(&s_InputPin, INPUT_CHANNEL_COUNT, NULL);
    if (ret != 0)
    {
        printf("awe_initPin inputPin failed\n");
    }
    ret = awe_initPin(&s_OutputPin, OUTPUT_CHANNEL_COUNT, NULL);
    if (ret != 0)
    {
        printf("awe_initPin outputPin failed\n");
    }



#if HAS_FLASH_FILESYSTEM

    // Setup the flash file system
    memset(&g_AWEFlashFSInstance, 0, sizeof(AWEFlashFSInstance) );

    g_AWEFlashFSInstance.cbInit = &usrInitFlashFileSystem;
    g_AWEFlashFSInstance.cbEraseSector = &usrEraseFlashMemorySector;
    g_AWEFlashFSInstance.cbFlashWrite = &usrWriteFlashMemory;
    g_AWEFlashFSInstance.cbFlashRead = &usrReadFlashMemory;

    g_AWEFlashFSInstance.flashSizeInBytes = FLASH_MEMORY_SIZE_IN_BYTES;
    g_AWEFlashFSInstance.flashErasableBlockSizeInBytes = ERASEABLE_BLOCKSIZE;
    g_AWEFlashFSInstance.flashStartOffsetInBytes = FILE_SYSTEM_START_OFFSET;
    g_AWEFlashFSInstance.flashEraseTimeInMs = 0;

    awe_initFlashFS(&g_AWEInstance, &g_AWEFlashFSInstance);

#endif

    // User version word
    g_AWEInstance.userVersion = USER_VER;

    // Initialize board properties
    g_AWEInstance.instanceId = INSTANCE_ID;
    g_AWEInstance.coreSpeed = CORE_SPEED;
    g_AWEInstance.profileSpeed = CORE_SPEED;
    g_AWEInstance.pName = "ST32F407";
    g_AWEInstance.numThreads = NUM_AUDIO_THREADS;
    g_AWEInstance.pModuleDescriptorTable = g_module_descriptor_table;
    g_AWEInstance.numModules = g_module_descriptor_table_size;
    g_AWEInstance.sampleRate = AUDIO_SAMPLE_RATE;
    g_AWEInstance.fundamentalBlockSize = AUDIO_BLOCK_SIZE;

    // Define the heap sizes
    g_AWEInstance.fastHeapASize = FASTA_HEAP_SIZE;
    g_AWEInstance.fastHeapBSize = FASTB_HEAP_SIZE;
    g_AWEInstance.slowHeapSize = SLOW_HEAP_SIZE;

    // Point to the heaps on this target
    g_AWEInstance.pFastHeapA = g_fastA_heap;
    g_AWEInstance.pFastHeapB = g_fastB_heap;
    g_AWEInstance.pSlowHeap = g_slow_heap;

    // Define storage for the tuning packet buffer
    g_AWEInstance.pPacketBuffer = g_packet_buffer;
    g_AWEInstance.packetBufferSize = MAX_COMMAND_BUFFER_LEN;

    g_AWEInstance.pReplyBuffer = g_packet_buffer;

    // Initialize the AWE instance
    ret = awe_init(&g_AWEInstance);
    if (ret != 0)
    {
        printf("awe_init failed\n");
    }

}   // End AWEInstanceInit

/**
  * @brief  InitCycleCounter
  * @param  None
  * @retval None
  */
void InitCycleCounter(void)
{
    *SCB_DEMCR   = *SCB_DEMCR | 0x01000000;
    *LAR         = 0xC5ACCE55;             // unlock access to DWT (ITM, etc.)registers
    *DWT_CYCCNT  = 0;                      // reset the counter
    *DWT_CONTROL = *DWT_CONTROL | 1 ;      // enable the counter

}   // End InitCycleCounter

//-----------------------------------------------------------------------------
// METHOD:  aweuser_getCycleCount
// PURPOSE: Returns the current value in the counter
//-----------------------------------------------------------------------------
UINT32 aweuser_getCycleCount(void)
{
    return *DWT_CYCCNT;

}   // End aweuser_getCycleCount

//-----------------------------------------------------------------------------
// METHOD:  aweuser_getElapsedCycles
// PURPOSE: Returns the cycle count between start time and end time
//-----------------------------------------------------------------------------
UINT32 aweuser_getElapsedCycles(UINT32 nStartTime, UINT32 nEndTime)
{
	return nEndTime - nStartTime;

}   // End aweuser_getElapsedCycles

//-----------------------------------------------------------------------------
// METHOD:  usrInitFlashFileSystem
// PURPOSE: This method is here
//-----------------------------------------------------------------------------
AWE_OPTIMIZE_FOR_SPACE
AWE_FW_SLOW_CODE
BOOL usrInitFlashFileSystem(void)
{
    // Clear the flash register flags
    __HAL_FLASH_CLEAR_FLAG( (FLASH_FLAG_EOP | \
                             FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | \
                             FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR));

    return SUCCESS;

}   // End usrInitFlashFileSystem


//-----------------------------------------------------------------------------
// METHOD:  usrReadFlashMemory
// PURPOSE: Read from flash memory device
//-----------------------------------------------------------------------------
AWE_OPTIMIZE_FOR_SPACE
AWE_FW_SLOW_CODE
BOOL usrReadFlashMemory(UINT32 nFlashAddress, UINT32 * pBuffer, UINT32 nDWordsToRead)
{
    UINT32 n;
    UINT32 * pSrc = (UINT32 *)nFlashAddress;

	for (n = 0; n < nDWordsToRead; n++)
	{
		pBuffer[n] = pSrc[n];
	}

	return SUCCESS;

}	// End usrReadFlashMemory


//-----------------------------------------------------------------------------
// METHOD:  usrWriteFlashMemory
// PURPOSE: Write to flash memory device
//-----------------------------------------------------------------------------
AWE_OPTIMIZE_FOR_SPACE
AWE_FW_SLOW_CODE
BOOL usrWriteFlashMemory(UINT32 nFlashAddress, UINT32 * pBuffer, UINT32 nDWordsToWrite)
{
	UINT32 n = 0;

	// Flash address must be on a 4 byte boundary since writing DWords
	if ( (nFlashAddress & 0x00000003) != 0)
	{
		return FAILURE;
	}

    HAL_FLASH_Unlock();

    while (n < nDWordsToWrite)
    {
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, nFlashAddress, pBuffer[n]) == HAL_OK)
        {
            // Read back DWORD that was written
            DWORD nDWord;
            nDWord = *(PDWORD)nFlashAddress;
            if (nDWord != pBuffer[n])
            {
                return FAILURE;
            }

            nFlashAddress = nFlashAddress + 4;
            n++;
        }
        else
        {
            return FAILURE;
        }
    }

    HAL_FLASH_Lock();

	return SUCCESS;

}	// End usrWriteFlashMemory


//-----------------------------------------------------------------------------
// METHOD:  usrEraseFlashMemorySector
// PURPOSE: Erase Flash Memory used for Flash File System
//          The flash memory region assigned for the flash file system
//          starts with flash sector 8. These are actually 128K sectors.
//-----------------------------------------------------------------------------
AWE_OPTIMIZE_FOR_SPACE
AWE_FW_SLOW_CODE
BOOL usrEraseFlashMemorySector(UINT32 nStartingAddress, UINT32 nNumberOfSectors)
{
    FLASH_EraseInitTypeDef EraseInitStruct;
    UINT32 nSector_to_erase = 0;
    UINT32 SectorError = 0;

    if (nStartingAddress < ADDR_FLASH_SECTOR_7)
    {
        nSector_to_erase = FLASH_SECTOR_6;
    }

    else if (nStartingAddress < ADDR_FLASH_SECTOR_8)
    {
        nSector_to_erase = FLASH_SECTOR_7;
    }

    else if (nStartingAddress < ADDR_FLASH_SECTOR_9)
    {
        nSector_to_erase = FLASH_SECTOR_8;
    }

    else if (nStartingAddress < ADDR_FLASH_SECTOR_10)
    {
        nSector_to_erase = FLASH_SECTOR_9;
    }

    else if (nStartingAddress < ADDR_FLASH_SECTOR_11)
    {
        nSector_to_erase = FLASH_SECTOR_10;
    }

    else if (nStartingAddress < ((uint32_t)0x08100000))
    {
        nSector_to_erase = FLASH_SECTOR_11;
    }

    HAL_FLASH_Unlock();

    EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
    EraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;
    EraseInitStruct.Sector = nSector_to_erase;
    EraseInitStruct.NbSectors = nNumberOfSectors;

    if (HAL_FLASHEx_Erase(&EraseInitStruct, (uint32_t *)&SectorError) != HAL_OK)
    {
        return FAILURE;
    }

    __HAL_FLASH_DATA_CACHE_DISABLE();
    __HAL_FLASH_DATA_CACHE_RESET();
    __HAL_FLASH_DATA_CACHE_ENABLE();

    HAL_FLASH_Lock();

	return SUCCESS;

}	// End usrEraseFlashMemorySector

//-----------------------------------------------------------------------------
// METHOD:  awe_pltGPIOSetPinDir
// PURPOSE: Set GPIO pin direction
//-----------------------------------------------------------------------------
void awe_pltGPIOSetPinDir(UINT32 nPinNo, UINT32 nPinDir)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    UINT32 nPinNdx;

    if (nPinNo < 1 || nPinNo > MAX_PINS)
    {
        return;
    }

    // If user wants control of LED4 relinquish board alive LED toggle
    if (nPinNo == 3 && nPinDir != GPIO_DIR_INPUT)
    {
        g_bBlinkLED4ForBoardAlive = FALSE;
    }

    nPinNdx = nPinNo - 1;

    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Pull = GPIO_NOPULL;

    if (nPinDir == GPIO_DIR_INPUT)
    {
        GPIO_InitStruct.Pin = InputPinMap[nPinNdx].GPIO_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;

        // Setup the GPIO pin
        HAL_GPIO_Init(InputPinMap[nPinNdx].GPIOx, &GPIO_InitStruct);
    }
    else
    {
        GPIO_InitStruct.Pin = OutputPinMap[nPinNdx].GPIO_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;

        // Setup the GPIO pin
        HAL_GPIO_Init(OutputPinMap[nPinNdx].GPIOx, &GPIO_InitStruct);

        // Initialize output pin to 0
        awe_pltGPIOSetPin(nPinNo, 0);
    }

}   // End awe_pltGPIOSetPinDir


//-----------------------------------------------------------------------------
// METHOD:  awe_pltGPIOTogglePin
// PURPOSE: Set GBPIO pin value
//-----------------------------------------------------------------------------
void awe_pltGPIOTogglePin(UINT32 nPinNo)
{
    UINT32 nPinNdx;

    if (nPinNo < 1 || nPinNo > MAX_PINS)
    {
        return;
    }

    nPinNdx = nPinNo - 1;

    HAL_GPIO_TogglePin(OutputPinMap[nPinNdx].GPIOx, OutputPinMap[nPinNdx].GPIO_Pin);

}   // End awe_pltGPIOTogglePin


//-----------------------------------------------------------------------------
// METHOD:  awe_pltGPIOSetPin
// PURPOSE: Set GBPIO pin value
//-----------------------------------------------------------------------------
void awe_pltGPIOSetPin(UINT32 nPinNo, UINT32 nValue)
{
    UINT32 nPinNdx;

    if (nPinNo < 1 || nPinNo > MAX_PINS)
    {
        return;
    }

    nPinNdx = nPinNo - 1;

    if (nValue > 0)
    {
        HAL_GPIO_WritePin(OutputPinMap[nPinNdx].GPIOx, OutputPinMap[nPinNdx].GPIO_Pin, GPIO_PIN_SET);
     }
    else
    {
        HAL_GPIO_WritePin(OutputPinMap[nPinNdx].GPIOx, OutputPinMap[nPinNdx].GPIO_Pin, GPIO_PIN_RESET);
    }

}   // End awe_pltGPIOSetPin


//-----------------------------------------------------------------------------
// METHOD:  awe_pltGPIOGetPin
// PURPOSE: Get GPIO pin value
//-----------------------------------------------------------------------------
void awe_pltGPIOGetPin(UINT32 nPinNo, UINT32 * nValue)
{
    UINT32 nPinNdx;

    if (nPinNo < 1 || nPinNo > MAX_PINS)
    {
        return;
    }

    nPinNdx = nPinNo - 1;

    *nValue = HAL_GPIO_ReadPin(InputPinMap[nPinNdx].GPIOx, InputPinMap[nPinNdx].GPIO_Pin);

}   // End awe_pltGPIOGetPin


