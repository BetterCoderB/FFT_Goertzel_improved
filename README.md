# Modified Goertzel algorithm

The Goertzel algorithm is a special implementation of the Discrete Fourier Transform (DFT) in the form of a recursive filter.
Unlike the Fast Fourier Transform, which calculates all frequency components of the DFT, the Goertzel algorithm allows you to efficiently calculate the value of a single frequency component.
The modified Goertzel algorithm allows us to recalculate a given spectral sample at each sampling cycle. This library implements the algorithm in Arduino IDE for Teensy 4.x:

Example fed signal:
![Signal](https://github.com/BetterCoderB/FFT_Goertzel_improved/blob/main/Signal.png)
The result is a time-frequency-level representation of the signal:
![Time-frequency-level](https://github.com/BetterCoderB/FFT_Goertzel_improved/blob/main/Goertzel.gif)

These images for clarity were implemented in excel

In most cases at multiple frequencies real-time processing can be used

Before starting, the DATA_SIZE sample size is determined.
The frequencies of interest are the frequency indices written in frequency_k[]
Calculate the number of required frequencies quantity_k.
The class

	Goertzel<DATA_SIZE, (int*)frequency_k, quantity_k> FFT_Goertzel is defined;

For each sampling cycle, use:

	FFT_Goertzel.write(adc_value); //or signal value
  
	FFT_Goertzel.getmax();// and immediately get the maximum value (if necessary) 

Read in loop:

	FFT_Goertzel.read(i); //value without averaging

Modified Goertzel algorithm from Sergey Bakhurin
http://www.dsplib.ru/content/goertzelmod/goertzelmod.html
