#include "folowing.hpp"

 // This tick() function handles sample computation only.  It will be
 // called automatically when the system needs a new buffer of audio
 // samples.
 int tick( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
         double streamTime, RtAudioStreamStatus status, void *dataPointer )
 {
   SineWave *sine = (SineWave *) dataPointer;
   register StkFloat *samples = (StkFloat *) outputBuffer;
   for ( unsigned int i=0; i<nBufferFrames; i++ )
     *samples++ = sine->tick();
   return 0;
 }

void	init_sound(RtAudio *dac)
{
  // Set the global sample rate before creating class instances.
  Stk::setSampleRate( 96000.0 );
  SineWave sine;
  // Figure out how many bytes in an StkFloat and setup the RtAudio stream.
  RtAudio::StreamParameters parameters;
  parameters.deviceId = (*dac).getDefaultOutputDevice();
  parameters.nChannels = 1;
  RtAudioFormat format = ( sizeof(StkFloat) == 8 ) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
  unsigned int bufferFrames = RT_BUFFER_SIZE;
  try {
    (*dac).openStream( &parameters, NULL, format, (unsigned int)Stk::sampleRate(), &bufferFrames, &tick, (void *)&sine );
  }
  catch ( RtAudioError &error ) {
    error.printMessage();
  }
  sine.setFrequency(440.0);
  try {
    (*dac).startStream();
  }
  catch ( RtAudioError &error ) {
    error.printMessage();
  }
}

void	multi_sound(t_centre *zone)
{
	double x, y;


	for (int i = 0; i < MAX_BALL ; i++)
	{
		if (zone[i].size > 0)
		{
			x = zone[i].sum_x / zone[i].size;
			y = zone[i].sum_y / zone[i].size;
  //			sine.setFrequency(x);
		}
	}
}

void	close_sound(RtAudio dac)
{
  // Shut down the output stream.
  try {
    dac.closeStream();
  }
  catch ( RtAudioError &error ) {
    error.printMessage();
  }
}


