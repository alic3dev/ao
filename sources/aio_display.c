#include <aio_display.h>

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

  aio_display->index_y_previous = 0;
}

void aio_display_next(
  struct aio_display* aio_display
) {
  for (
    unsigned int index_y = 0;
    index_y < aio_display->renderer.size.height;
    ++index_y
  ) {
    for (
      unsigned int index_x = 0;
      index_x < aio_display->renderer.size.width - 1;
      ++index_x
    ) {
      aio_display->renderer.pixels[index_y][index_x] = (
        aio_display->renderer.pixels[index_y][index_x + 1]
      );
      
      aio_display->renderer.pixels[index_y][index_x + 1] = 0;
    }
  }
}

void aio_display_update(
  struct aio_display* aio_display,
  float frequency
) {
  unsigned int index_y = (
    (((int)(
      (((float)aio_display->renderer.size.height) * frequency) / 2.0f
    )) + (aio_display->renderer.size.height / 2)) % aio_display->renderer.size.height
  );

  unsigned int index_x = (
    aio_display->renderer.size.width - 1
  );

  aio_display->renderer.pixels[
    index_y
  ][
    index_x
  ] = 1;

  if (aio_display->index_y_previous > index_y) {
    unsigned int distance_y_half = (
      aio_display->index_y_previous - index_y
    ) / 2;

    for (
      unsigned int index_y_pixel = index_y;
      index_y_pixel < aio_display->index_y_previous;
      ++index_y_pixel
    ) {
      aio_display->renderer.pixels[
        index_y_pixel
      ][
        (aio_display->index_y_previous - index_y_pixel) < distance_y_half
        ? index_x - 1
        : index_x
      ] = 1;
    }
  } else if (aio_display->index_y_previous < index_y) {
    unsigned int distance_y_half = (
      index_y - aio_display->index_y_previous
    ) / 2;

    for (
      unsigned int index_y_pixel = aio_display->index_y_previous;
      index_y_pixel < index_y;
      ++index_y_pixel
    ) {
      aio_display->renderer.pixels[
        index_y_pixel
      ][
        (aio_display->index_y_previous - index_y_pixel) < distance_y_half
        ? index_x - 1
        : index_x
      ] = 1;
    }
  }

  aio_display->index_y_previous = index_y;
}

void aio_display_render(
  struct aio_display* aio_display
) {
  cexil_renderer_render(
    &aio_display->renderer
  );
}

