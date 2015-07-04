#pragma once
#include <random>
#include <thread>
#include <vector>

#include <cmath>
#include <cstdio>


#ifndef TAU_SEED
#define TAU_SEED 0xC4D3E2F1
#endif
#ifndef TAU_SAMPLES_LINEAR
#define TAU_SAMPLES_LINEAR    10000000.  // takes ~3 seconds on my PC
#endif
#ifndef TAU_SAMPLES_THREADED
#define TAU_SAMPLES_THREADED  10000000.
#endif
#ifndef TAU_THREADS
#define TAU_THREADS           100
#endif

typedef unsigned int uint;


template <class returntype=double, class countertype=double>
returntype CalcTauLinear(countertype num_samples) {
  countertype num_internal = 0;

  std::mt19937_64 mt(TAU_SEED);
  std::uniform_real_distribution<double> dist(0.0, 1.0);

  // sample a bunch of points
  for (countertype i = 0; i < num_samples; ++i) {
    if (pow(dist(mt), 2.) + pow(dist(mt), 2.) < 1.) {
      ++num_internal;
    }
  }

  // ratio determines value of tau
  returntype ret = num_internal;
  ret /= num_samples;
  ret *= 8;
  //printf("(%.0f / %.0f)*8  =  %f\n", num_internal, num_samples, ret);
  return ret;
}


template <class returntype=double, class countertype=double>
returntype CalcTauThreaded(countertype num_samples, uint num_threads) {
  countertype   num_internal_total = 0;
  std::vector<countertype> num_internal(num_threads, 0);

  // lambda to run on each thread
  auto helper = [&num_internal, &num_threads, &num_samples](uint i) {
    std::mt19937_64 mt(TAU_SEED + i);
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    auto frac = num_samples / num_threads;
    auto low = uint( frac*i );
    auto high = uint (low + frac );
    //printf("\n%u   %u-%u", i, low, high);

    for (uint j = low; j < high; ++j) {
      if (pow(dist(mt), 2.) + pow(dist(mt), 2.) < 1.) {
        num_internal[i] += 1;
      }
    }
  };

  // launch and join threads
  std::vector<std::thread> threads(num_threads);
  for (uint i = 0; i < num_threads; ++i)
    threads[i] = std::thread(helper, i);
  for (auto& thread : threads) thread.join();

  // sum the sums
  for (uint i = 0; i < num_threads; ++i) 
    num_internal_total += num_internal[i];
 
  // determine final result
  returntype ret = num_internal_total;
  ret /= num_samples;
  ret *= 8;
  return ret;
}
