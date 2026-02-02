#ifndef __ao_parameters_h
#define __ao_parameters_h

struct ao_parameters {
  unsigned char export;
  unsigned char play;
  char* path_export;

  unsigned char block;

  char octave_minimum;
  char octave_maximum;

  unsigned long int speed;
  
  unsigned char synced_oscillator;
  
  unsigned char visualizer;
  unsigned char visualizer_average;

  unsigned char help;
};

int ao_parameters_parse(
  struct ao_parameters*,
  int,
  char**
);

#endif
