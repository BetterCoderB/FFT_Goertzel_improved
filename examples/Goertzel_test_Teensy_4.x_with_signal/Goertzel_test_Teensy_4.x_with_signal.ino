#include <Arduino.h>
#include <ADC.h>
#include <ADC_util.h>
ADC* adc = new ADC();

const int DATA_SIZE = 2048;  //buffer
const int frequency = 20480; //frequency
/* 
20480Hz / 2048 * 77 = 770 Hz
            ...78 = 780 Hz
            ...79 = 790 Hz
            ............
*/
const int frequency_k[] = { 
  77,
  78,
  79,
  80,
  81,
  82,
  83,
}; //lane numbers

const int quantity_k = sizeof(frequency_k) / sizeof(int);
#include <FFT_Goertzel_improved.h>
Goertzel<DATA_SIZE, frequency,(const int*)frequency_k, quantity_k> FFT_Goertzel;

#include "signal.h"
const int quantity_sample = sizeof(signal) / sizeof(float);

void setup() {
  Serial.begin(115200);
  adc->adc0->setResolution(12);
  adc->adc0->setReference(ADC_REFERENCE::REF_3V3);
while(!Serial);
  float value;
  float max_level;
  int i;
  int j;
  for (j = 0; j < quantity_sample; j++) {
    
    //shift relative to zero
    value = signal[j];  
    //write down the value
    FFT_Goertzel.write(value);         
    //get the maximum value in the given sample
    max_level = FFT_Goertzel.getmax();  

    for (i = 0; i < quantity_k; i++) {
      value = (FFT_Goertzel.getamplitude(i));  //normalize received value
      Serial.print(value);
      Serial.print(' ');
    }
     Serial.print(" ");
    Serial.print(' ');
    for (i = 0; i < quantity_k; i++) {
      value = (FFT_Goertzel.getfriquency(i));  //normalize received value
      Serial.print(value,2);
      Serial.print(' ');
    }
    Serial.println();
    delay(1);
  };
}
void loop() {
  
}