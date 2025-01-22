/*******************************************************************************
*
*               Audio Framework
*               ---------------
*
********************************************************************************
*     ModuleList.h
********************************************************************************
*
* -----------------------------------------------------------------------------
* Specifies the audio modules that will be linked into the target application
* -----------------------------------------------------------------------------
*
*     Copyright:    DSP Concepts, Inc., 2007 - 2020
*                   3235 Kifer Road, Suite 100
*                   Santa Clara, CA 95051
*
*******************************************************************************/


#ifndef _MODULELIST_H
#define _MODULELIST_H

#ifdef	__cplusplus
extern "C" {
#endif

// Standard Modules
extern const int awe_modAGCCoreClass;
extern const int awe_modAGCLimiterCoreClass;
extern const int awe_modAGCLimiterCoreFract32Class;
extern const int awe_modAGCLimiterCoreV2Class;
extern const int awe_modAGCLimiterCoreV2Fract32Class;
extern const int awe_modAGCMultiplierFract32Class;
extern const int awe_modAGCNoiseGateCoreClass;
extern const int awe_modAbsClass;
extern const int awe_modAbsFract32Class;
extern const int awe_modAcosClass;
extern const int awe_modAdderClass;
extern const int awe_modAdderFract32Class;
extern const int awe_modAdderInt32Class;
extern const int awe_modAsinClass;
extern const int awe_modAtanClass;
extern const int awe_modAtan2Class;
extern const int awe_modBalanceClass;
extern const int awe_modBalanceFract32Class;
extern const int awe_modBiquadClass;
extern const int awe_modBiquadCascadeClass;
extern const int awe_modBiquadCascadeFract32Class;
extern const int awe_modBiquadFract32Class;
extern const int awe_modBiquadNCascadeClass;
extern const int awe_modBiquadSmoothedClass;
extern const int awe_modBiquadSmoothedFract32Class;
extern const int awe_modBiquadV2Fract32Class;
extern const int awe_modBitsToIntClass;
extern const int awe_modBlockCounterClass;
extern const int awe_modBooleanInvertClass;
extern const int awe_modBooleanSinkClass;
extern const int awe_modBooleanSourceClass;
extern const int awe_modButterworthFilterClass;
extern const int awe_modButterworthFilterFract32Class;
extern const int awe_modCeilClass;
extern const int awe_modClipAsymClass;
extern const int awe_modClipAsymFract32Class;
extern const int awe_modClipAsymInt32Class;
extern const int awe_modClipIndicatorClass;
extern const int awe_modClipIndicatorFract32Class;
extern const int awe_modCopierClass;
extern const int awe_modCosClass;
extern const int awe_modCoshClass;
extern const int awe_modCounterClass;
extern const int awe_modCrossFaderClass;
extern const int awe_modDCSourceIntClass;
extern const int awe_modDCSourceV2Class;
extern const int awe_modDCSourceV2Fract32Class;
extern const int awe_modDb10Class;
extern const int awe_modDb10ApproxClass;
extern const int awe_modDb10Fract32Class;
extern const int awe_modDb20Class;
extern const int awe_modDb20ApproxClass;
extern const int awe_modDb20Fract32Class;
extern const int awe_modDcBlockClass;
extern const int awe_modDebounceClass;
extern const int awe_modDeinterleaveClass;
extern const int awe_modDelayClass;
extern const int awe_modDelayMsecClass;
extern const int awe_modDivideClass;
extern const int awe_modExpClass;
extern const int awe_modFIRClass;
extern const int awe_modFIRFract32Class;
extern const int awe_modFIRSmoothedClass;
extern const int awe_modFloorClass;
extern const int awe_modFmodClass;
extern const int awe_modFrexpClass;
extern const int awe_modGPIOClass;
extern const int awe_modGraphicEQBandClass;
extern const int awe_modGraphicEQBandFract32Class;
extern const int awe_modImpulseMsecSourceClass;
extern const int awe_modImpulseMsecSourceFract32Class;
extern const int awe_modImpulseSourceFract32Class;
extern const int awe_modIntToBitsClass;
extern const int awe_modInterleaveClass;
extern const int awe_modInvertClass;
extern const int awe_modInvertFract32Class;
extern const int awe_modLShiftFract32Class;
extern const int awe_modLdexpClass;
extern const int awe_modLinkwitzRileyFilterClass;
extern const int awe_modLogClass;
extern const int awe_modLog10Class;
extern const int awe_modLog10Fract32Class;
extern const int awe_modLog2Class;
extern const int awe_modLog2Fract32Class;
extern const int awe_modLogicAllClass;
extern const int awe_modLogicAndConstFract32Class;
extern const int awe_modLogicAndConstInt32Class;
extern const int awe_modLogicAnyClass;
extern const int awe_modLogicBinaryOpClass;
extern const int awe_modLogicCompareClass;
extern const int awe_modLogicCompareConstClass;
extern const int awe_modLogicCompareConstFract32Class;
extern const int awe_modLogicCompareConstInt32Class;
extern const int awe_modLogicCompareConstReplaceClass;
extern const int awe_modLogicCompareConstReplaceInt32Class;
extern const int awe_modLogicCompareFract32Class;
extern const int awe_modLogicCompareInt32Class;
extern const int awe_modMaxAbsClass;
extern const int awe_modMaxAbsFract32Class;
extern const int awe_modMeterClass;
extern const int awe_modMeterFract32Class;
extern const int awe_modMixerDenseFract32Class;
extern const int awe_modMixerFract32Class;
extern const int awe_modMixerSmoothedFract32Class;
extern const int awe_modMixerV3Class;
extern const int awe_modMixerV3Fract32Class;
extern const int awe_modModfClass;
extern const int awe_modMultiplexorClass;
extern const int awe_modMultiplexorV2Class;
extern const int awe_modMultiplexorV2Fract32Class;
extern const int awe_modMultiplierFract32Class;
extern const int awe_modMultiplierV2Class;
extern const int awe_modMultiplierV2Fract32Class;
extern const int awe_modMuteNSmoothedClass;
extern const int awe_modMuteNSmoothedFract32Class;
extern const int awe_modMuteSmoothedClass;
extern const int awe_modMuteSmoothedFract32Class;
extern const int awe_modMuteUnmuteClass;
extern const int awe_modMuteUnmuteFract32Class;
extern const int awe_modNullSinkClass;
extern const int awe_modNullSinkV2Class;
extern const int awe_modNullSourceClass;
extern const int awe_modParamGetClass;
extern const int awe_modParamSetClass;
extern const int awe_modPeriodicFunctionGenClass;
extern const int awe_modPeriodicSourceClass;
extern const int awe_modPeriodicSourceFract32Class;
extern const int awe_modPolynomialClass;
extern const int awe_modPolynomialFract32Class;
extern const int awe_modPowClass;
extern const int awe_modPow10toXClass;
extern const int awe_modPow2Fract32Class;
extern const int awe_modPowFract32Class;
extern const int awe_modPulseGenClass;
extern const int awe_modPulseGenFract32Class;
extern const int awe_modRMSClass;
extern const int awe_modRMSFract32Class;
extern const int awe_modRMSNClass;
extern const int awe_modRandClass;
extern const int awe_modReciprocalClass;
extern const int awe_modReciprocalFract32Class;
extern const int awe_modRemainderClass;
extern const int awe_modRoundClass;
extern const int awe_modRouterClass;
extern const int awe_modRouterSmoothedClass;
extern const int awe_modRouterSmoothedFract32Class;
extern const int awe_modSMixer2x1Class;
extern const int awe_modSMixer2x1Fract32Class;
extern const int awe_modSOFSmoothedCascadeFract32Class;
extern const int awe_modSawtoothFract32Class;
extern const int awe_modScaleOffsetClass;
extern const int awe_modScaleOffsetFract32Class;
extern const int awe_modScaleOffsetInt32Class;
extern const int awe_modScalerControlClass;
extern const int awe_modScalerControlBlockSmoothedFract32Class;
extern const int awe_modScalerControlSmoothedFract32Class;
extern const int awe_modScalerDBControlClass;
extern const int awe_modScalerDBFract32Class;
extern const int awe_modScalerDBSmoothedFract32Class;
extern const int awe_modScalerFract32Class;
extern const int awe_modScalerNControlClass;
extern const int awe_modScalerNDBSmoothedFract32Class;
extern const int awe_modScalerNFract32Class;
extern const int awe_modScalerNSmoothedFract32Class;
extern const int awe_modScalerNSymmetricFadingClass;
extern const int awe_modScalerNV2Class;
extern const int awe_modScalerSmoothedFract32Class;
extern const int awe_modScalerSymmetricFadingClass;
extern const int awe_modScalerSymmetricFadingV2Class;
extern const int awe_modScalerV2Class;
extern const int awe_modSecondOrderFilterSmoothedClass;
extern const int awe_modSecondOrderFilterSmoothedCascadeClass;
extern const int awe_modSecondOrderFilterSmoothedCascadeV2Class;
extern const int awe_modSecondOrderFilterSmoothedFract32Class;
extern const int awe_modShiftFract32Class;
extern const int awe_modSignClass;
extern const int awe_modSinClass;
extern const int awe_modSineGenControlFract32Class;
extern const int awe_modSineGenFract32Class;
extern const int awe_modSineSmoothedGenClass;
extern const int awe_modSineSmoothedGenFract32Class;
extern const int awe_modSinhClass;
extern const int awe_modSinkClass;
extern const int awe_modSinkFract32Class;
extern const int awe_modSinkFract32PropertiesClass;
extern const int awe_modSinkIntClass;
extern const int awe_modSinkIntPropertiesClass;
extern const int awe_modSinkPropertiesClass;
extern const int awe_modSofV2HpFract32Class;
extern const int awe_modSoftClipClass;
extern const int awe_modSoftClipFract32Class;
extern const int awe_modSoloMuteClass;
extern const int awe_modSoloMuteFract32Class;
extern const int awe_modSourceClass;
extern const int awe_modSourceFract32Class;
extern const int awe_modSourceFract32PropertiesClass;
extern const int awe_modSourceIntClass;
extern const int awe_modSourceIntPropertiesClass;
extern const int awe_modSourcePropertiesClass;
extern const int awe_modSqrtClass;
extern const int awe_modSqrtFract32Class;
extern const int awe_modSquareClass;
extern const int awe_modSquareAddClass;
extern const int awe_modSquareAddFract32Class;
extern const int awe_modSquareFract32Class;
extern const int awe_modSubtractClass;
extern const int awe_modSubtractFract32Class;
extern const int awe_modSubtractInt32Class;
extern const int awe_modSumDiffClass;
extern const int awe_modSumDiffFract32Class;
extern const int awe_modSumDiffInt32Class;
extern const int awe_modTableInterpClass;
extern const int awe_modTableInterpFract32Class;
extern const int awe_modTableLookupClass;
extern const int awe_modTableLookupV2Class;
extern const int awe_modTanClass;
extern const int awe_modTanhClass;
extern const int awe_modThreeBandToneControlClass;
extern const int awe_modThreeBandToneControlFract32Class;
extern const int awe_modToggleButtonClass;
extern const int awe_modTypeConversionClass;
extern const int awe_modUndb10Class;
extern const int awe_modUndb10ApproxClass;
extern const int awe_modUndb10Fract32Class;
extern const int awe_modUndb20Class;
extern const int awe_modUndb20ApproxClass;
extern const int awe_modUndb20Fract32Class;
extern const int awe_modVolumeControlClass;
extern const int awe_modVolumeControlFract32Class;
extern const int awe_modWetDryClass;
extern const int awe_modWhiteNoiseClass;
extern const int awe_modWhiteNoiseFract32Class;
extern const int awe_modWithinRangeClass;
extern const int awe_modWithinRangeFract32Class;
extern const int awe_modZeroCrossingDetectorClass;
extern const int awe_modZeroCrossingDetectorFract32Class;
extern const int awe_modZeroSourceClass;


// Advanced Modules


// Deprecated Modules


// Internal Modules
extern const int awe_modCompiledSubsystemClass;
extern const int awe_modFifoInClass;
extern const int awe_modFifoInV2Class;
extern const int awe_modFifoOutClass;
extern const int awe_modFifoOutV2Class;
extern const int awe_modIPCFifoInClass;
extern const int awe_modIPCFifoOutClass;
extern const int awe_modProxyGetSetClass;


// Additional Modules
extern const int awe_modSTBassManagerClass;
extern const int awe_modSTBiquadCascadeClass;
extern const int awe_modSTGainManagerClass;
extern const int awe_modSTGraphicEqClass;
extern const int awe_modSTHeadphoneVirtClass;
extern const int awe_modSTOmni2Class;
extern const int awe_modSTOmniSurroundClass;
extern const int awe_modSTSMRClass;
extern const int awe_modSTSmartVolumeClass;
extern const int awe_modSTSoundDetectClass;



// Edit this list to prune modules from target
#define STANDARD_LIST \
&awe_modAGCCoreClass, \
&awe_modAGCLimiterCoreClass, \
&awe_modAGCLimiterCoreV2Class, \
&awe_modAGCNoiseGateCoreClass, \
&awe_modAbsClass, \
&awe_modAcosClass, \
&awe_modAdderClass, \
&awe_modAdderInt32Class, \
&awe_modAsinClass, \
&awe_modAtanClass, \
&awe_modAtan2Class, \
&awe_modBalanceClass, \
&awe_modBiquadClass, \
&awe_modBiquadCascadeClass, \
&awe_modBiquadNCascadeClass, \
&awe_modBiquadSmoothedClass, \
&awe_modBitsToIntClass, \
&awe_modBlockCounterClass, \
&awe_modBooleanInvertClass, \
&awe_modBooleanSinkClass, \
&awe_modBooleanSourceClass, \
&awe_modButterworthFilterClass, \
&awe_modCeilClass, \
&awe_modClipAsymClass, \
&awe_modClipAsymInt32Class, \
&awe_modClipIndicatorClass, \
&awe_modCopierClass, \
&awe_modCosClass, \
&awe_modCoshClass, \
&awe_modCounterClass, \
&awe_modCrossFaderClass, \
&awe_modDCSourceIntClass, \
&awe_modDCSourceV2Class, \
&awe_modDb10Class, \
&awe_modDb10ApproxClass, \
&awe_modDb20Class, \
&awe_modDb20ApproxClass, \
&awe_modDcBlockClass, \
&awe_modDebounceClass, \
&awe_modDeinterleaveClass, \
&awe_modDelayClass, \
&awe_modDelayMsecClass, \
&awe_modDivideClass, \
&awe_modExpClass, \
&awe_modFIRClass, \
&awe_modFIRSmoothedClass, \
&awe_modFloorClass, \
&awe_modFmodClass, \
&awe_modFrexpClass, \
&awe_modGPIOClass, \
&awe_modGraphicEQBandClass, \
&awe_modImpulseMsecSourceClass, \
&awe_modIntToBitsClass, \
&awe_modInterleaveClass, \
&awe_modInvertClass, \
&awe_modLdexpClass, \
&awe_modLinkwitzRileyFilterClass, \
&awe_modLogClass, \
&awe_modLog10Class, \
&awe_modLog2Class, \
&awe_modLogicAllClass, \
&awe_modLogicAndConstInt32Class, \
&awe_modLogicAnyClass, \
&awe_modLogicBinaryOpClass, \
&awe_modLogicCompareClass, \
&awe_modLogicCompareConstClass, \
&awe_modLogicCompareConstInt32Class, \
&awe_modLogicCompareConstReplaceClass, \
&awe_modLogicCompareConstReplaceInt32Class, \
&awe_modLogicCompareInt32Class, \
&awe_modMaxAbsClass, \
&awe_modMeterClass, \
&awe_modMixerV3Class, \
&awe_modModfClass, \
&awe_modMultiplexorClass, \
&awe_modMultiplexorV2Class, \
&awe_modMultiplierV2Class, \
&awe_modMuteNSmoothedClass, \
&awe_modMuteSmoothedClass, \
&awe_modMuteUnmuteClass, \
&awe_modNullSinkClass, \
&awe_modNullSinkV2Class, \
&awe_modNullSourceClass, \
&awe_modParamGetClass, \
&awe_modParamSetClass, \
&awe_modPeriodicFunctionGenClass, \
&awe_modPeriodicSourceClass, \
&awe_modPolynomialClass, \
&awe_modPowClass, \
&awe_modPow10toXClass, \
&awe_modPulseGenClass, \
&awe_modRMSClass, \
&awe_modRMSNClass, \
&awe_modRandClass, \
&awe_modReciprocalClass, \
&awe_modRemainderClass, \
&awe_modRoundClass, \
&awe_modRouterClass, \
&awe_modRouterSmoothedClass, \
&awe_modSMixer2x1Class, \
&awe_modScaleOffsetClass, \
&awe_modScaleOffsetInt32Class, \
&awe_modScalerControlClass, \
&awe_modScalerDBControlClass, \
&awe_modScalerNControlClass, \
&awe_modScalerNSymmetricFadingClass, \
&awe_modScalerNV2Class, \
&awe_modScalerSymmetricFadingClass, \
&awe_modScalerSymmetricFadingV2Class, \
&awe_modScalerV2Class, \
&awe_modSecondOrderFilterSmoothedClass, \
&awe_modSecondOrderFilterSmoothedCascadeClass, \
&awe_modSecondOrderFilterSmoothedCascadeV2Class, \
&awe_modSignClass, \
&awe_modSinClass, \
&awe_modSineSmoothedGenClass, \
&awe_modSinhClass, \
&awe_modSinkClass, \
&awe_modSinkIntClass, \
&awe_modSinkIntPropertiesClass, \
&awe_modSinkPropertiesClass, \
&awe_modSoftClipClass, \
&awe_modSoloMuteClass, \
&awe_modSourceClass, \
&awe_modSourceIntClass, \
&awe_modSourceIntPropertiesClass, \
&awe_modSourcePropertiesClass, \
&awe_modSqrtClass, \
&awe_modSquareClass, \
&awe_modSquareAddClass, \
&awe_modSubtractClass, \
&awe_modSubtractInt32Class, \
&awe_modSumDiffClass, \
&awe_modSumDiffInt32Class, \
&awe_modTableInterpClass, \
&awe_modTableLookupClass, \
&awe_modTableLookupV2Class, \
&awe_modTanClass, \
&awe_modTanhClass, \
&awe_modThreeBandToneControlClass, \
&awe_modToggleButtonClass, \
&awe_modTypeConversionClass, \
&awe_modUndb10Class, \
&awe_modUndb10ApproxClass, \
&awe_modUndb20Class, \
&awe_modUndb20ApproxClass, \
&awe_modVolumeControlClass, \
&awe_modWetDryClass, \
&awe_modWhiteNoiseClass, \
&awe_modWithinRangeClass, \
&awe_modZeroCrossingDetectorClass, \
&awe_modZeroSourceClass

#define ADVANCED_LIST 

#define DEPRECATED_LIST 

#define INTERNAL_LIST \
&awe_modCompiledSubsystemClass, \
&awe_modFifoInClass, \
&awe_modFifoInV2Class, \
&awe_modFifoOutClass, \
&awe_modFifoOutV2Class, \
&awe_modIPCFifoInClass, \
&awe_modIPCFifoOutClass, \
&awe_modProxyGetSetClass

#define CUSTOM_LIST \
&awe_modSTBassManagerClass, \
&awe_modSTBiquadCascadeClass, \
&awe_modSTGainManagerClass, \
&awe_modSTGraphicEqClass, \
&awe_modSTHeadphoneVirtClass, \
&awe_modSTOmni2Class, \
&awe_modSTOmniSurroundClass, \
&awe_modSTSMRClass, \
&awe_modSTSmartVolumeClass, \
&awe_modSTSoundDetectClass


#define LISTOFCLASSOBJECTS \
STANDARD_LIST, \
CUSTOM_LIST



#ifdef	__cplusplus
}
#endif

#endif	// _MODULELIST_H
