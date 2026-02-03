#include <aio_display.h>

#include <aio_display_thread.h>

#include <cexil.h>

void aio_display_initialize(
  struct aio_display* aio_display
) {
  struct cexil_size size_terminal;

  cexil_size_set_to_terminal(
    &size_terminal
  );

  cexil_renderer_initialize(
    &aio_display->renderer,
    &size_terminal
  );

  cexil_sprite_initialize(
    &aio_display->sprite,
    &size_terminal
  );

  cexil_renderer_sprite_add(
    &aio_display->renderer,
    &aio_display->sprite
  );

  aio_display_thread_data_initialize(
    &aio_display->data_thread,
    aio_display
  );

  aio_display->index_y_previous = 0;

  pthread_create(
    &aio_display->thread,
    0,
    aio_display_thread,
    &aio_display->data_thread
  );
}

void aio_display_update(
  struct aio_display* aio_display,
  float frequency
) {
  aio_display->sprite.render_offset.x = (
    (
      aio_display->sprite.render_offset.x +
      1
    ) %
    aio_display->renderer.size.width
  );

  unsigned int index_y_frequency = (
    (((int)(
      (((float)aio_display->sprite.size.height - 1) * frequency) / 2.0f
    )) + ((aio_display->sprite.size.height - 1) / 2)) % (aio_display->sprite.size.height - 1)
  );

  unsigned int distance_y_half = 0;

  if (
    aio_display->index_y_previous > index_y_frequency
  ) {
    distance_y_half = (
      aio_display->index_y_previous - index_y_frequency
    ) / 2;
  } else if (
    aio_display->index_y_previous < index_y_frequency
  ) {
    distance_y_half = (
      index_y_frequency - aio_display->index_y_previous
    ) / 2;
  }

  unsigned int offset_pixel_x_negative = (
    aio_display->sprite.render_offset.x == 0
    ? (
      aio_display->sprite.size.width -
      1
    )
    : (
      aio_display->sprite.render_offset.x -
      1
    )
  );

  for (
    unsigned int index_y_pixel = 0;
    index_y_pixel < aio_display->sprite.size.height;
    ++index_y_pixel
  ) {
    aio_display->sprite.pixels[
      index_y_pixel
    ][
      (aio_display->index_y_previous - index_y_pixel) < distance_y_half
      ? offset_pixel_x_negative
      : aio_display->sprite.render_offset.x
    ] = (
      aio_display->index_y_previous > index_y_frequency
      ? (
        index_y_pixel >= index_y_frequency &&
        index_y_pixel <= aio_display->index_y_previous
      )
      : (
        index_y_pixel >= aio_display->index_y_previous &&
        index_y_pixel <= index_y_frequency
      )
    );
  }

  aio_display->index_y_previous = (
    index_y_frequency
  );
}

void aio_display_render(
  struct aio_display* aio_display
) {
  pthread_mutex_unlock(
    &aio_display->data_thread.mutex_render
  );
}

void aio_display_destroy(
  struct aio_display* aio_display
) {
  aio_display->data_thread.running = 0;

  pthread_mutex_unlock(
    &aio_display->data_thread.mutex_queue
  );

  pthread_mutex_unlock(
    &aio_display->data_thread.mutex_render
  );

  pthread_join(
    aio_display->thread,
    0
  );

  aio_display_thread_data_destroy(
    &aio_display->data_thread
  );

  cexil_renderer_destroy(
    &aio_display->renderer
  );
}
