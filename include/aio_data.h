#ifndef __aio_data_h
#define __aio_data_h

#include <aio_display.h>

#include <cer0.h>

enum mode_aio_data {
  play,
  export,
  export_play
};

struct aio_data {
  unsigned char initialized;

  FILE** file_inputs;
  unsigned int length_file_inputs;

  unsigned char exporting;
  FILE* file_output;

  float* note_table;
  unsigned int length_note_table;

  struct cer0_oscillator oscillator;

  enum mode_aio_data mode;

  struct aio_display display;
  unsigned char visualizer;
};

#endif
