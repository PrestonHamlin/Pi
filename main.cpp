#include "tau.h"

using namespace std;

int main() {
  double tau_linear = 0.0;
  
  // calculate tau with a linear processing of samples
  tau_linear = CalcTauLinear<double,double>(TAU_SAMPLES_LINEAR);


  printf("\n===== RESULTS FOR TAU =====\n"
         "Linear evaluation of %.0f samples: \n\t%.015f\n\n"
         "\n",
         TAU_SAMPLES_LINEAR, tau_linear
         );


  printf("\nhave a nice day\n");
  return 0;
}
