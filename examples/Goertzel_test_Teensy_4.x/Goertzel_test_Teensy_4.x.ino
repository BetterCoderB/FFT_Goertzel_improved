#include <Arduino.h>
#include <ADC.h>
#include <ADC_util.h>
ADC* adc = new ADC();

const int DATA_SIZE = 256;
const int frequency_k[] = { 30, 31, 32 };
/* 
5120Hz / 256 * 30 = 600 Hz
            ...31 = 620 Hz
            ...32 = 640 Hz
*/
const int quantity_k = sizeof(frequency_k) / sizeof(int);

#include <FFT_Goertzel_improved.h>
Goertzel<DATA_SIZE, (const int*)frequency_k, quantity_k> FFT_Goertzel;


void setup() {
  Serial.begin(115200);
  adc->adc0->setResolution(12);
  adc->adc0->setReference(ADC_REFERENCE::REF_3V3);
}
void loop() {
  long timer;
  int value;
  int max_level;
  int i;
  while (1) {
    //timer sampling timer
    timer = micros();
    //shift relative to zero
    value = analogRead(A8) - 1560;
    //write down the value
    FFT_Goertzel.write(value);
    //get the maximum value in the given sample
    max_level = FFT_Goertzel.getmax();

    for (i = 0; i < quantity_k; i++) {
      value = (FFT_Goertzel.read(i) / max_level * 99);  //normalize received value
      Serial.print((int)value);
      Serial.print(' ');
    }
    Serial.println();

    //latency for fine sampling - 5120Hz this: 195.312us
    while (micros() - timer < 195)
      ;
    delayNanoseconds(312);  //Teency 4.x
  };
}