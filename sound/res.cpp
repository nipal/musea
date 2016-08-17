#include "BiQuad.h"
#include "Noise.h"
using namespace stk;
int main()
{
  StkFrames output( 20, 1 );   // initialize StkFrames to 20 frames and 1 channel (default: interleaved)
  Noise noise;
  BiQuad biquad;
  biquad.setResonance( 440.0, 0.98, true ); // automatically normalize for unity peak gain
  for ( unsigned int i=0; i<output.size(); i++ ) {
    output[i] = biquad.tick( noise.tick() );  // single-sample computations
    std::cout << "i = " << i << " : output = " << output[i] << std::endl;
  }
  return 0;
}

