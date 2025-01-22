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

#ifndef AWE_REVERB_WITH_MUX_CONTROLINTERFACE_H
#define AWE_REVERB_WITH_MUX_CONTROLINTERFACE_H

// ----------------------------------------------------------------------
//  [Delay]
// Newly created subsystem

#define AWE_Delay1_classID 0xBEEF0800
#define AWE_Delay1_ID 30005

// int profileTime - 24.8 fixed point filtered execution time. Must be pumped 1000 times to get to within .1% accuracy
#define AWE_Delay1_profileTime_HANDLE 0x07535007
#define AWE_Delay1_profileTime_MASK 0x00000080
#define AWE_Delay1_profileTime_SIZE 0x00000001

// int maxDelay - Maximum delay, in samples. The size of the delay 
//         buffer is maxDelay*numChannels.
#define AWE_Delay1_maxDelay_HANDLE 0x07535008
#define AWE_Delay1_maxDelay_MASK 0x00000100
#define AWE_Delay1_maxDelay_SIZE 0x00000001

// int currentDelay - Current delay.
// Default value: 2900
// Range: 0 to 3000.  Step size = 1
#define AWE_Delay1_currentDelay_HANDLE 0x07535009
#define AWE_Delay1_currentDelay_MASK 0x00000200
#define AWE_Delay1_currentDelay_SIZE 0x00000001

// int stateIndex - Index of the oldest state variable in the array of 
//         state variables.
#define AWE_Delay1_stateIndex_HANDLE 0x0753500A
#define AWE_Delay1_stateIndex_MASK 0x00000400
#define AWE_Delay1_stateIndex_SIZE 0x00000001

// int stateHeap - Heap in which to allocate memory.
#define AWE_Delay1_stateHeap_HANDLE 0x0753500B
#define AWE_Delay1_stateHeap_MASK 0x00000800
#define AWE_Delay1_stateHeap_SIZE 0x00000001

// float state[3001] - State variable array.
#define AWE_Delay1_state_HANDLE 0x8753500C
#define AWE_Delay1_state_MASK 0x00001000
#define AWE_Delay1_state_SIZE 0x00000BB9


// ----------------------------------------------------------------------
//  [ScalerV2]
// Newly created subsystem

#define AWE_Scaler1_classID 0xBEEF0813
#define AWE_Scaler1_ID 30002

// int profileTime - 24.8 fixed point filtered execution time. Must be pumped 1000 times to get to within .1% accuracy
#define AWE_Scaler1_profileTime_HANDLE 0x07532007
#define AWE_Scaler1_profileTime_MASK 0x00000080
#define AWE_Scaler1_profileTime_SIZE 0x00000001

// float gain - Gain in either linear or dB units.
// Default value: -3
// Range: -24 to 24
#define AWE_Scaler1_gain_HANDLE 0x07532008
#define AWE_Scaler1_gain_MASK 0x00000100
#define AWE_Scaler1_gain_SIZE 0x00000001

// float smoothingTime - Time constant of the smoothing process (0 = 
//         unsmoothed).
// Default value: 10
// Range: 0 to 1000
#define AWE_Scaler1_smoothingTime_HANDLE 0x07532009
#define AWE_Scaler1_smoothingTime_MASK 0x00000200
#define AWE_Scaler1_smoothingTime_SIZE 0x00000001

// int isDB - Selects between linear (=0) and dB (=1) operation
// Default value: 1
// Range: 0 to 1
#define AWE_Scaler1_isDB_HANDLE 0x0753200A
#define AWE_Scaler1_isDB_MASK 0x00000400
#define AWE_Scaler1_isDB_SIZE 0x00000001

// float targetGain - Target gain in linear units.
#define AWE_Scaler1_targetGain_HANDLE 0x0753200B
#define AWE_Scaler1_targetGain_MASK 0x00000800
#define AWE_Scaler1_targetGain_SIZE 0x00000001

// float currentGain - Instantaneous gain applied by the module.
#define AWE_Scaler1_currentGain_HANDLE 0x0753200C
#define AWE_Scaler1_currentGain_MASK 0x00001000
#define AWE_Scaler1_currentGain_SIZE 0x00000001

// float smoothingCoeff - Smoothing coefficient.
#define AWE_Scaler1_smoothingCoeff_HANDLE 0x0753200D
#define AWE_Scaler1_smoothingCoeff_MASK 0x00002000
#define AWE_Scaler1_smoothingCoeff_SIZE 0x00000001


// ----------------------------------------------------------------------
//  [MultiplexorV2]
// Newly created subsystem

#define AWE_Multiplexor1_classID 0xBEEF0868
#define AWE_Multiplexor1_ID 30034

// int profileTime - 24.8 fixed point filtered execution time. Must be pumped 1000 times to get to within .1% accuracy
#define AWE_Multiplexor1_profileTime_HANDLE 0x07552007
#define AWE_Multiplexor1_profileTime_MASK 0x00000080
#define AWE_Multiplexor1_profileTime_SIZE 0x00000001

// int index - Specifies which input pin to route to the output. The 
//         index is zero based.
// Default value: 1
// Range: 0 to 1
#define AWE_Multiplexor1_index_HANDLE 0x07552008
#define AWE_Multiplexor1_index_MASK 0x00000100
#define AWE_Multiplexor1_index_SIZE 0x00000001

// float smoothingTime - Time constant of the smoothing process
// Default value: 10
// Range: 0 to 100
#define AWE_Multiplexor1_smoothingTime_HANDLE 0x07552009
#define AWE_Multiplexor1_smoothingTime_MASK 0x00000200
#define AWE_Multiplexor1_smoothingTime_SIZE 0x00000001

// float fadeTime - Silence time in crossfade
// Default value: 0
// Range: 0 to 100
#define AWE_Multiplexor1_fadeTime_HANDLE 0x0755200A
#define AWE_Multiplexor1_fadeTime_MASK 0x00000400
#define AWE_Multiplexor1_fadeTime_SIZE 0x00000001

// int isControl - Indicates if the index is controlled by an external 
//         signal
#define AWE_Multiplexor1_isControl_HANDLE 0x0755200B
#define AWE_Multiplexor1_isControl_MASK 0x00000800
#define AWE_Multiplexor1_isControl_SIZE 0x00000001

// float smoothingCoeff - Smoothing coefficient
#define AWE_Multiplexor1_smoothingCoeff_HANDLE 0x0755200C
#define AWE_Multiplexor1_smoothingCoeff_MASK 0x00001000
#define AWE_Multiplexor1_smoothingCoeff_SIZE 0x00000001

// float oldSrcGain - Instanteous gain being applied to the old source.  
//         This is an internal variable used in the smoothing process
#define AWE_Multiplexor1_oldSrcGain_HANDLE 0x0755200D
#define AWE_Multiplexor1_oldSrcGain_MASK 0x00002000
#define AWE_Multiplexor1_oldSrcGain_SIZE 0x00000001

// float newSrcGain - Instanteous gain being applied to the new source.  
//         This is an internal variable used in the smoothing process
#define AWE_Multiplexor1_newSrcGain_HANDLE 0x0755200E
#define AWE_Multiplexor1_newSrcGain_MASK 0x00004000
#define AWE_Multiplexor1_newSrcGain_SIZE 0x00000001

// int fadeState - State variable for determining when to transitioning 
//         between inputs
#define AWE_Multiplexor1_fadeState_HANDLE 0x0755200F
#define AWE_Multiplexor1_fadeState_MASK 0x00008000
#define AWE_Multiplexor1_fadeState_SIZE 0x00000001

// int fadeStateInit - Derived from fadeTime, determines number of 
//         blocks to wait before switching input pins
#define AWE_Multiplexor1_fadeStateInit_HANDLE 0x07552010
#define AWE_Multiplexor1_fadeStateInit_MASK 0x00010000
#define AWE_Multiplexor1_fadeStateInit_SIZE 0x00000001

// int oldIndex - This is the index that is currently being used
// Default value: 1
// Range: unrestricted
#define AWE_Multiplexor1_oldIndex_HANDLE 0x07552011
#define AWE_Multiplexor1_oldIndex_MASK 0x00020000
#define AWE_Multiplexor1_oldIndex_SIZE 0x00000001

// int newIndex - This is the index being transitioned to
// Default value: 1
// Range: unrestricted
#define AWE_Multiplexor1_newIndex_HANDLE 0x07552012
#define AWE_Multiplexor1_newIndex_MASK 0x00040000
#define AWE_Multiplexor1_newIndex_SIZE 0x00000001


#define AWE_OBJECT_FOUND 0

#endif // AWE_REVERB_WITH_MUX_CONTROLINTERFACE_H

