#ifndef __aio_data_h
#define __aio_data_h

#include <cer0.h>

struct aio_data {
  unsigned char initialized;

  FILE** file_inputs;
  unsigned int length_file_inputs;

  float* note_table;
  unsigned int length_note_table;

  struct cer0_oscillator oscillator;
};

#endif
