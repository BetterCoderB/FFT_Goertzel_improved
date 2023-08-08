#include <Arduino.h>
#include <ADC.h>
#include <ADC_util.h>
ADC* adc = new ADC();

const int DATA_SIZE = 256;
const int frequency_k[] = {1,  2,  3,  4,  5,  6,  7,  8,  9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,  64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79,  80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95,  96,  97,  98,  99,  100,  101,  102,  103,  104,  105,  106,  107,  108,  109,  110,  111,  112,  113,  114,  115,  116,  117,  118,  119,  120,  121,  122,  123,  124,  125,  126,  127,
};
/* 
5120Hz / 256 * 1 = 20 Hz
            ...2 = 40 Hz
            ...3 = 60 Hz
*/

const int quantity_k = sizeof(frequency_k) / sizeof(int);
#include <FFT_Goertzel_improved.h>
Goertzel<DATA_SIZE, (int*)frequency_k, quantity_k> FFT_Goertzel;

//#include <signal.h>
float signal[] = {
  
};
const int quantity_sample = sizeof(signal) / sizeof(float);

void setup() {
  Serial.begin(115200);
  adc->adc0->setResolution(12);
  adc->adc0->setReference(ADC_REFERENCE::REF_3V3);

  float value;
  float max_level;
  int i;
  int j;
  for (j = 0; j < quantity_sample; j++) {
    
    value = signal[j];  //shift relative to zero
    FFT_Goertzel.write(value);          //write down the value
    max_level = FFT_Goertzel.getmax();  //get the maximum value in the given sample

    for (i = 0; i < quantity_k; i++) {
      value = (FFT_Goertzel.read(i) / max_level * 99);  //normalize received value
      Serial.print((int)value);
      Serial.print(' ');
    }
    Serial.println();
    delay(50);
  };
}
void loop() {
  
}