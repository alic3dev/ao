#ifndef __aio_export_h
#define __aio_export_h

#include <aio_data.h>

#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mutex_exporting;

int aio_export_write(
  FILE*,
  float
);

void aio_export_data(
  struct aio_data*
);

#endif
