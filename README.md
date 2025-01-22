# Exploratory-DSP-Workshops

This repository contains instructions and supporting files for four workshops exploring theory and applications of digital signal processing (DSP).

## FFT and STFT for classification of spoken digits

The Fast Fourier Transform (FFT) is an essential engineering tool. In this workshop we will review the interpretation of the FFT and its extension to the short-time Fourier transform (STFT). Using python, you will present STFT audio features as input to a neural network  to recognize spoken digits, and test the network on your own speech. No previous knowledge of FFTs or python needed.

## Audio Weaver on the STM32F407 Discovery Board

In this workshop, you will use Audio Weaver, a graphical audio design interface, to create audio applications involving gains, delays, and filters. These application will run on your PC with input from youTube. You will then prepare your projects to run standalone on the STM32F407 Discovery microcontroller board. No experience needed.

## Using ARM CMSIS DSP Library for filtering and FFT functions

The open source CMSIS DSP library provides DSP functions that can be used on all ARM processors. In this workshop you will design a filter in MATLAB and test it on the STM32F407 Discovery board with library filter functions. In addition you use library functions to take a Fast Fourier Transform (FFT) of your input signal, and examine the results in STM32CubeIDE, the integrated development environment for STM32 chips. No experience needed.

## Control of Audio Weaver blocks on STM32F407 Discovery board

This workshop adds real time control to the standalone operation of Audio Weaver code on the STM32F407 Discovery board. You will build a DC offset circuit and a variable voltage divider on a breadboard to control the audio qualities of a reverberation effect, in the manner of a microcontroller DSP product. Attending the “Audio Weaver on the STM32F407 Discovery Board” workshop before attending this one would be advantageous.
