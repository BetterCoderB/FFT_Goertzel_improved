#ifndef _FFT_GOERTZEL_IMPROVED_H
#define _FFT_GOERTZEL_IMPROVED_H
#pragma once
#include <Arduino.h>

template <const int DATA_SIZE, const int frequency, const int *frequency_k, int quantity_k> class Goertzel {
public:
  Goertzel();
  float read(int k){return magnitude[k];};                       //sqrt(real*real+image*image)
  float getamplitude(int k){return magnitude[k]/(DATA_SIZE/2);};     //sqrt(real*real+image*image)/DATA_SIZE
  float getphase(int k){return phase[k];};
  float getfriquency(int k){return friquency[k];}; //5120 / (2);};
  float getmax(){
    value_max_buffer = value_max;
    value_max = 0;
    return value_max_buffer;
    };
  void write(float value);
private:
  float signal_buffer[(DATA_SIZE + 1)];

  float SN_k0[2][quantity_k];         //real & image
  float SN_k0_buff[2][quantity_k];    //real & image
  float W_N[2][quantity_k];           //real & image
  float W_sn[quantity_k];             //real
  float ln_W[quantity_k];             //ln(W) - exponent degree

  float SN_k0_pow2[2][quantity_k];    //real^2 & image^2

  float SN_buffer_real[quantity_k];   //x1 real
  float sN_signal_buffer_read[2];     //x[DATA_SIZE] & x[-1]
  float magnitude[quantity_k];
  
  float phase[quantity_k];
  
  float dt4[7][quantity_k];
  float dt04[7][quantity_k];
  float friquency[quantity_k];
  
  float value_max = 0;
  float value_max_buffer = 0;
  int i;
  int n;
  int count = 0;
};

template <const int DATA_SIZE, const int frequency, const int *frequency_k, int quantity_k> Goertzel<DATA_SIZE, frequency, frequency_k, quantity_k>::Goertzel() { 
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
template <const int DATA_SIZE, const int frequency, const int *frequency_k, int quantity_k> void Goertzel<DATA_SIZE, frequency, frequency_k, quantity_k>::write(float value) {
  signal_buffer[count % (DATA_SIZE + 1)] = value;                                          // write value
  if (++count >= (DATA_SIZE + 1)) count = 0;
  sN_signal_buffer_read[0] = signal_buffer[(DATA_SIZE + count) % (DATA_SIZE + 1)];         // x[DATA_SIZE]
  sN_signal_buffer_read[1] = signal_buffer[(0 + count) % (DATA_SIZE + 1)];                 // x[-1]
  for (i = 0; i < quantity_k; i++) {
    SN_buffer_real[i] = SN_k0[0][i] + sN_signal_buffer_read[0] - sN_signal_buffer_read[1];  //x1
        
    SN_k0[0][i] = SN_buffer_real[i] * W_N[0][i] - SN_k0[1][i] * W_N[1][i];                  //(x1+iy1) * (x2+iy2) => real: x1*x2-y1*y2
    SN_k0[1][i] = SN_buffer_real[i] * W_N[1][i] + SN_k0[1][i] * W_N[0][i];                  //(x1+iy1) * (x2+iy2) => image: x1*y2+y1*x2
    
    SN_k0_pow2[0][i]=SN_k0[0][i]*SN_k0[0][i];
    SN_k0_pow2[1][i]=SN_k0[1][i]*SN_k0[1][i];

    magnitude[i] = sqrt(SN_k0_pow2[0][i] + SN_k0_pow2[1][i]);
    if (magnitude[i] > value_max) value_max = magnitude[i];

    phase[i] = atan2(SN_k0[1][i],SN_k0[0][i]);

    dt4[6][i] = phase[i];
    if (dt4[6][i]-(PI/2) > dt4[0][i]) {
    for (n = 0; n < 7; n++) {
      dt04[n][i] = dt4[n][i];
      }
    } else {
      dt04[6][i] = dt4[6][i] + 2 * PI; 
      while(dt04[6][i] < dt04[5][i]){dt04[6][i] = dt04[6][i] + 2 * PI;}
    }; 
    friquency[i] = (dt04[6][i] - 9 * dt04[5][i] + 45 * dt04[4][i] - 45 * dt04[2][i] + 9 * dt04[1][i] - dt04[0][i]) / 60 * frequency/(2*PI);

    for (n = 0; n < 6; n++) {
      dt4[n][i] = dt4[n + 1][i];
      dt04[n][i] = dt04[n + 1][i];
    };
  }
}
#endif