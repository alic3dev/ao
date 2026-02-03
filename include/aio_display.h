#ifndef __aio_display_h
#define __aio_display_h

#include <cexil.h>

struct aio_display {
  struct cexil_renderer renderer;
  struct cexil_sprite sprite;

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
