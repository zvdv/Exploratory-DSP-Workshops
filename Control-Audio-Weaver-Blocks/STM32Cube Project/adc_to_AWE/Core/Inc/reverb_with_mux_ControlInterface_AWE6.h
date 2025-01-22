/****************************************************************************
 *
 *		Target Tuning Symbol File
 *		-------------------------
 *
 * 		This file is populated with symbol information only for modules
 *		that have an object ID of 30000 or greater assigned.
 *
 *          Generated on:  01-Sep-2024 19:31:12
 *
 ***************************************************************************/

#ifndef AWE_REVERB_WITH_MUX_CONTROLINTERFACE_AWE6_H
#define AWE_REVERB_WITH_MUX_CONTROLINTERFACE_AWE6_H

// ----------------------------------------------------------------------
// Delay1 [Delay]
// Time delay in which the delay is specified in samples

#define AWE_Delay1_ID 30005

// int profileTime - 24.8 fixed point filtered execution time. Must be pumped 1000 times to get to within .1% accuracy
#define AWE_Delay1_profileTime_OFFSET 7
#define AWE_Delay1_profileTime_MASK 0x00000080
#define AWE_Delay1_profileTime_SIZE -1

// int maxDelay - Maximum delay, in samples. The size of the delay 
//         buffer is maxDelay*numChannels.
#define AWE_Delay1_maxDelay_OFFSET 8
#define AWE_Delay1_maxDelay_MASK 0x00000100
#define AWE_Delay1_maxDelay_SIZE -1

// int currentDelay - Current delay.
// Default value: 2900
// Range: 0 to 3000.  Step size = 1
#define AWE_Delay1_currentDelay_OFFSET 9
#define AWE_Delay1_currentDelay_MASK 0x00000200
#define AWE_Delay1_currentDelay_SIZE -1

// int stateIndex - Index of the oldest state variable in the array of 
//         state variables.
#define AWE_Delay1_stateIndex_OFFSET 10
#define AWE_Delay1_stateIndex_MASK 0x00000400
#define AWE_Delay1_stateIndex_SIZE -1

// int stateHeap - Heap in which to allocate memory.
#define AWE_Delay1_stateHeap_OFFSET 11
#define AWE_Delay1_stateHeap_MASK 0x00000800
#define AWE_Delay1_stateHeap_SIZE -1

// float state[3001] - State variable array.
#define AWE_Delay1_state_OFFSET 12
#define AWE_Delay1_state_MASK 0x00001000
#define AWE_Delay1_state_SIZE 3001


// ----------------------------------------------------------------------
// Scaler1 [ScalerV2]
// General purpose scaler with a single gain

#define AWE_Scaler1_ID 30002

// int profileTime - 24.8 fixed point filtered execution time. Must be pumped 1000 times to get to within .1% accuracy
#define AWE_Scaler1_profileTime_OFFSET 7
#define AWE_Scaler1_profileTime_MASK 0x00000080
#define AWE_Scaler1_profileTime_SIZE -1

// float gain - Gain in either linear or dB units.
// Default value: -3
// Range: -24 to 24
#define AWE_Scaler1_gain_OFFSET 8
#define AWE_Scaler1_gain_MASK 0x00000100
#define AWE_Scaler1_gain_SIZE -1

// float smoothingTime - Time constant of the smoothing process (0 = 
//         unsmoothed).
// Default value: 10
// Range: 0 to 1000
#define AWE_Scaler1_smoothingTime_OFFSET 9
#define AWE_Scaler1_smoothingTime_MASK 0x00000200
#define AWE_Scaler1_smoothingTime_SIZE -1

// int isDB - Selects between linear (=0) and dB (=1) operation
// Default value: 1
// Range: 0 to 1
#define AWE_Scaler1_isDB_OFFSET 10
#define AWE_Scaler1_isDB_MASK 0x00000400
#define AWE_Scaler1_isDB_SIZE -1

// float targetGain - Target gain in linear units.
#define AWE_Scaler1_targetGain_OFFSET 11
#define AWE_Scaler1_targetGain_MASK 0x00000800
#define AWE_Scaler1_targetGain_SIZE -1

// float currentGain - Instantaneous gain applied by the module.
#define AWE_Scaler1_currentGain_OFFSET 12
#define AWE_Scaler1_currentGain_MASK 0x00001000
#define AWE_Scaler1_currentGain_SIZE -1

// float smoothingCoeff - Smoothing coefficient.
#define AWE_Scaler1_smoothingCoeff_OFFSET 13
#define AWE_Scaler1_smoothingCoeff_MASK 0x00002000
#define AWE_Scaler1_smoothingCoeff_SIZE -1


// ----------------------------------------------------------------------
// Multiplexor1 [MultiplexorV2]
// General purpose multiplexor

#define AWE_Multiplexor1_ID 30034

// int profileTime - 24.8 fixed point filtered execution time. Must be pumped 1000 times to get to within .1% accuracy
#define AWE_Multiplexor1_profileTime_OFFSET 7
#define AWE_Multiplexor1_profileTime_MASK 0x00000080
#define AWE_Multiplexor1_profileTime_SIZE -1

// int index - Specifies which input pin to route to the output. The 
//         index is zero based.
// Default value: 1
// Range: 0 to 1
#define AWE_Multiplexor1_index_OFFSET 8
#define AWE_Multiplexor1_index_MASK 0x00000100
#define AWE_Multiplexor1_index_SIZE -1

// float smoothingTime - Time constant of the smoothing process
// Default value: 10
// Range: 0 to 100
#define AWE_Multiplexor1_smoothingTime_OFFSET 9
#define AWE_Multiplexor1_smoothingTime_MASK 0x00000200
#define AWE_Multiplexor1_smoothingTime_SIZE -1

// float fadeTime - Silence time in crossfade
// Default value: 0
// Range: 0 to 100
#define AWE_Multiplexor1_fadeTime_OFFSET 10
#define AWE_Multiplexor1_fadeTime_MASK 0x00000400
#define AWE_Multiplexor1_fadeTime_SIZE -1

// int isControl - Indicates if the index is controlled by an external 
//         signal
#define AWE_Multiplexor1_isControl_OFFSET 11
#define AWE_Multiplexor1_isControl_MASK 0x00000800
#define AWE_Multiplexor1_isControl_SIZE -1

// float smoothingCoeff - Smoothing coefficient
#define AWE_Multiplexor1_smoothingCoeff_OFFSET 12
#define AWE_Multiplexor1_smoothingCoeff_MASK 0x00001000
#define AWE_Multiplexor1_smoothingCoeff_SIZE -1

// float oldSrcGain - Instanteous gain being applied to the old source.  
//         This is an internal variable used in the smoothing process
#define AWE_Multiplexor1_oldSrcGain_OFFSET 13
#define AWE_Multiplexor1_oldSrcGain_MASK 0x00002000
#define AWE_Multiplexor1_oldSrcGain_SIZE -1

// float newSrcGain - Instanteous gain being applied to the new source.  
//         This is an internal variable used in the smoothing process
#define AWE_Multiplexor1_newSrcGain_OFFSET 14
#define AWE_Multiplexor1_newSrcGain_MASK 0x00004000
#define AWE_Multiplexor1_newSrcGain_SIZE -1

// int fadeState - State variable for determining when to transitioning 
//         between inputs
#define AWE_Multiplexor1_fadeState_OFFSET 15
#define AWE_Multiplexor1_fadeState_MASK 0x00008000
#define AWE_Multiplexor1_fadeState_SIZE -1

// int fadeStateInit - Derived from fadeTime, determines number of 
//         blocks to wait before switching input pins
#define AWE_Multiplexor1_fadeStateInit_OFFSET 16
#define AWE_Multiplexor1_fadeStateInit_MASK 0x00010000
#define AWE_Multiplexor1_fadeStateInit_SIZE -1

// int oldIndex - This is the index that is currently being used
// Default value: 1
// Range: unrestricted
#define AWE_Multiplexor1_oldIndex_OFFSET 17
#define AWE_Multiplexor1_oldIndex_MASK 0x00020000
#define AWE_Multiplexor1_oldIndex_SIZE -1

// int newIndex - This is the index being transitioned to
// Default value: 1
// Range: unrestricted
#define AWE_Multiplexor1_newIndex_OFFSET 18
#define AWE_Multiplexor1_newIndex_MASK 0x00040000
#define AWE_Multiplexor1_newIndex_SIZE -1



#endif // AWE_REVERB_WITH_MUX_CONTROLINTERFACE_AWE6_H

