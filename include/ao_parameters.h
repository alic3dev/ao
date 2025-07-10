#ifndef __ao_parameters_h
#define __ao_parameters_h

struct ao_parameters {
  unsigned char export;
  unsigned char play;
  char* path_export;
  unsigned char visualizer;
};

int ao_parameters_parse(
  struct ao_parameters*,
  int,
  char**
);

#endif
