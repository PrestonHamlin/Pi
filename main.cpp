#include <iostream>
#include <iomanip>

#include "tau.h"

using namespace std;


int main() { 
  // calculate tau with a linear processing of samples
  auto tau_linear   = CalcTauLinear<double,double>(TAU_SAMPLES_LINEAR);

  // calculate tau with a threaded linear processing of samples
  auto tau_threaded = CalcTauThreaded(TAU_SAMPLES_THREADED, TAU_THREADS);


  cout << fixed;
  cout << "\n===== RESULTS FOR TAU =====\n";

  // linear (sector method)
  cout << setprecision(0)
       << "Linear    " << TAU_SAMPLES_LINEAR << " samples"
       << setprecision(15)
       << "\n\t" << tau_linear << endl << endl;

  // threaded (sector method)
  cout << setprecision(0)
       << "Threaded  " << TAU_SAMPLES_THREADED << " samples, "
                       << TAU_THREADS          << " threads"
       << setprecision(15)
       << "\n\t" << tau_threaded << endl << endl;
  cout << endl;


  printf("\nhave a nice day\n");
  return 0;
}
