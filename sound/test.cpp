// rtsine.cpp STK tutorial program
#include "SineWave.h"
#include "RtWvOut.h"
#include <cstdlib>

using namespace stk;

void	my_stk_init()
{
  // Set the global sample rate before creating class instances.
  Stk::setSampleRate( 44100.0 );
  Stk::showWarnings( true );
}

RtWvOut	*open_stream()
{
  RtWvOut *dac = 0;
  try {
    // Define and open the default realtime output device for one-channel playback
    dac = new RtWvOut( 1 );
  }
  catch ( StkError & ) {
    exit( 1 );
  }
  return (dac);
}

void	play_some(RtWvOut *dac)
{
  int nFrames = 100000;
  SineWave sine1;
  SineWave sine2;
  // Option 2: Single-sample computations
  for ( int i=0; i<nFrames; i++ )
  {
    sine1.setFrequency( (i * i * i) / 1000000);//441.0 );
    sine2.setFrequency( (nFrames * 440) / ((i + 100)));//441.0 );
//    try {
      dac->tick( sine1.tick() );
      dac->tick( sine2.tick() );
  //   }
 //   catch ( StkError & ) {
 //     goto cleanup;
//    }
  }

  for ( int i=0; i<nFrames; i++ )
  {
    sine1.setFrequency( (i * i * i) / 1000000);//441.0 );
    sine2.setFrequency( ((nFrames - i)));//441.0 );
//    try {
      dac->tick( sine1.tick() );
      dac->tick( sine2.tick() );
  //   }
 //   catch ( StkError & ) {
 //     goto cleanup;
//    }
  }
//  cleanup:
	return ;
   // delete dac;
}

void	close_stream()
{
}

int main()
{
  my_stk_init();

  RtWvOut	*dac = open_stream();

  play_some(dac);
//  close_stream();

  return 0;
}
  // Option 1: Use StkFrames
  /*
  StkFrames frames( nFrames, 1 );
  try {
    dac->tick( sine.tick( frames ) );
  }
  catch ( StkError & ) {
    goto cleanup;
  }
  */
