#ifndef __aio_display_h
#define __aio_display_h

#include <aio_display_thread.h>

#include <cexil.h>

#include <pthread.h>

struct aio_display {
  struct cexil_renderer renderer;
  struct cexil_sprite sprite;

  pthread_t thread;
  struct aio_display_thread_data data_thread;

  unsigned int index_y_previous;
};

void aio_display_initialize(
  struct aio_display*
);


void aio_display_update(
  struct aio_display*,
  float
);

void aio_display_render(
  struct aio_display*
);

void aio_display_destroy(
  struct aio_display*
);

#endif
