#ifndef __aio_display_thread_h
#define __aio_display_thread_h

#include <pthread.h>

struct aio_display_thread_data {
  void* display;

  float* queue;
  unsigned int length_queue;

  pthread_mutex_t mutex_queue;
  pthread_mutex_t mutex_render;

  unsigned char running;
};

void aio_display_thread_data_initialize(
  struct aio_display_thread_data*,
  void*
);

void aio_display_thread_queue_add(
  struct aio_display_thread_data*,
  float
);

void* aio_display_thread(
  void*
);

void aio_display_thread_data_destroy(
  struct aio_display_thread_data*
);

#endif
