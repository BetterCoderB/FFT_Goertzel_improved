#ifndef _FFT_GOERTZEL_IMPROVED_H
#define _FFT_GOERTZEL_IMPROVED_H
#pragma once
#include <Arduino.h>

template <const int DATA_SIZE, const int *frequency_k, int quantity_k> class Goertzel {
public:
  Goertzel();
  float read(int k){return level[k];};
  float getmax(){value_max_buffer = value_max;
                 value_max = 0;
                 return value_max_buffer;};
  void write(float value);
private:
  float signal_buffer[(DATA_SIZE + 1)];

  float SN_k0[2][quantity_k];         //real & image
  float SN_k0_buff[2][quantity_k];    //real & image
  float W_N[2][quantity_k];           //real & image
  float W_sn[quantity_k];             //real
  float ln_W[quantity_k];             //ln(W) - exponent degree

  float SN_buffer_real[quantity_k];   //x1 real
  float sN_signal_buffer_read[2];     //x[DATA_SIZE] & x[-1]
  float level[quantity_k];
  float value_max = 0;
  float value_max_buffer = 0;
  int i;
  int count = 0;
};

template <const int DATA_SIZE, const int *frequency_k, int quantity_k> Goertzel<DATA_SIZE, frequency_k,quantity_k>::Goertzel() { 
  for (i = 0; i < quantity_k; i++) {
    ln_W[i] = (2 * PI * frequency_k[i]) / DATA_SIZE;
    W_N[0][i] = cos(ln_W[i]);
    W_N[1][i] = sin(ln_W[i]);
    SN_k0[0][i] = 0;
    SN_k0[1][i] = 0;
    SN_k0_buff[0][i] = 0;
    SN_k0_buff[1][i] = 0;
  }
}
template <const int DATA_SIZE, const int *frequency_k, int quantity_k> void Goertzel<DATA_SIZE, frequency_k,quantity_k>::write(float value) {
  signal_buffer[count % (DATA_SIZE + 1)] = value;
  if (++count >= (DATA_SIZE + 1)) count = 0;
  sN_signal_buffer_read[0] = signal_buffer[(DATA_SIZE + count) % (DATA_SIZE + 1)];         // x[DATA_SIZE]
  sN_signal_buffer_read[1] = signal_buffer[(0 + count) % (DATA_SIZE + 1)];                 // x[-1]
  for (i = 0; i < quantity_k; i++) {
    SN_buffer_real[i] = SN_k0[0][i] + sN_signal_buffer_read[0] - sN_signal_buffer_read[1];  //x1
    SN_k0[0][i] = SN_buffer_real[i] * W_N[0][i] - SN_k0[1][i] * W_N[1][i];                  //(x1+iy1) * (x2+iy2) => real: x1*x2-y1*y2
    SN_k0[1][i] = SN_buffer_real[i] * W_N[1][i] + SN_k0[1][i] * W_N[0][i];                  //(x1+iy1) * (x2+iy2) => image: x1*y2+y1*x2
    level[i] = sqrt(SN_k0[0][i] * SN_k0[0][i] + SN_k0[1][i] * SN_k0[1][i]);                 //sqrt(real*real+image*image)
    if (level[i] > value_max) value_max = level[i];
  }
}
#endif