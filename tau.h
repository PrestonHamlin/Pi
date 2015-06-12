#pragma once
#include <random>

#include <cmath>
#include <cstdio>


#ifndef TAU_SEED
#define TAU_SEED 0xC4D3E2F1
#endif
#ifndef TAU_SAMPLES_LINEAR
#define TAU_SAMPLES_LINEAR 10000000.  // takes ~3 seconds on my PC
#endif


template <class returntype=double, class countertype=double>
returntype CalcTauLinear(countertype num_samples) {
  countertype num_internal = 0;
  returntype  ret = 0;

  std::mt19937_64 mt(TAU_SEED);
  std::uniform_real_distribution<double> dist(0.0, 1.0);

  // sample a bunch of points
  for (countertype i = 0; i < num_samples; ++i) {
    if (pow(dist(mt), 2.) + pow(dist(mt), 2.) < 1.) {
      ++num_internal;
    }
  }

  // ratio determines value of tau
  ret = (num_internal / num_samples) * 8;
  printf("(%.0f / %.0f)*2  =  %f\n", num_internal, num_samples, ret);

  return ret;
}
