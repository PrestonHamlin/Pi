#include "tau.h"

using namespace std;

int main() { 
  // calculate tau with a linear processing of samples
  auto tau_linear    = CalcTauLinear<double,double>(TAU_SAMPLES_LINEAR);

  // calculate tau with a threaded linear processing of samples
  auto tau_threaded = CalcTauThreaded(TAU_SAMPLES_THREADED, TAU_THREADS);

  printf("\n===== RESULTS FOR TAU =====\n"
         "Linear    %.0f samples:             \n\t%.015f\n\n"
         "Threaded  %.0f samples, %u threads: \n\t%.015f\n\n"
         "\n",
         TAU_SAMPLES_LINEAR, tau_linear,
         TAU_SAMPLES_THREADED, TAU_THREADS, tau_threaded
         );


  printf("\nhave a nice day\n");
  return 0;
}
