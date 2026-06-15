#include <aio_display_thread.h>

#include <aio_display.h>

#include <clic3_bytes.h>
#include <clic3_memory.h>

#include <pthread.h>

void aio_display_thread_data_initialize(
  struct aio_display_thread_data* aio_display_thread_data,
  void* display
) {
  aio_display_thread_data->display = (
    display
  );

  pthread_mutex_init(
    &aio_display_thread_data->mutex_queue,
    0x00
  );

  pthread_mutex_init(
    &aio_display_thread_data->mutex_render,
    0x00
  );

  aio_display_thread_data->length_queue = (
    0x00
  );

  aio_display_thread_data->queue = (
    clic3_memory_allocate_raw(
      0x00
    )
  );

  aio_display_thread_data->running = (
    0x01
  );
}

void aio_display_thread_queue_add(
  struct aio_display_thread_data* aio_display_thread_data,
  float frequency
) {
  pthread_mutex_lock(
    &aio_display_thread_data->mutex_queue
  );

  aio_display_thread_data->length_queue = (
    aio_display_thread_data->length_queue +
    0x01
  );

  clic3_memory_reallocate_raw(
    &aio_display_thread_data->queue,
    (
      sizeof(
        float
      ) *
      aio_display_thread_data->length_queue
    )
  );

  aio_display_thread_data->queue[
    aio_display_thread_data->length_queue -
    0x01
  ] = (
    frequency
  );

  pthread_mutex_unlock(
    &aio_display_thread_data->mutex_queue
  );
}

void* aio_display_thread(
  void* data_thread
) {
  struct aio_display_thread_data* aio_display_thread_data = (
    data_thread
  );

  struct aio_display* aio_display = (
    aio_display_thread_data->display
  );

  while(
    aio_display_thread_data->running ==
    0x01
  ) {
    pthread_mutex_lock(
      &aio_display_thread_data->mutex_render
    );

    pthread_mutex_lock(
      &aio_display_thread_data->mutex_queue
    );

    if (
      aio_display_thread_data->running !=
      0x01
    ) {
      pthread_mutex_unlock(
        &aio_display_thread_data->mutex_queue
      );

      pthread_mutex_unlock(
        &aio_display_thread_data->mutex_render
      );

      break;
    }

    unsigned int length_queue_buffered = (
      aio_display_thread_data->length_queue
    );

    float* queue_buffered = (
      clic3_memory_allocate_raw(
        sizeof(
          float
        ) *
        length_queue_buffered
      )
    );

    clic3_bytes_copy(
      queue_buffered,
      aio_display_thread_data->queue,
      length_queue_buffered
    );

    aio_display_thread_data->length_queue = (
      0x00
    );

    clic3_memory_reallocate_raw(
      &aio_display_thread_data->queue,
      0x00
    );

    pthread_mutex_unlock(
      &aio_display_thread_data->mutex_queue
    );

    for (
      unsigned int index_queue_buffered = (
        0x00
      );
      (
        index_queue_buffered <
        length_queue_buffered
      );
      ++index_queue_buffered
    ) {
      aio_display_update(
        aio_display,
        queue_buffered[
          index_queue_buffered
        ]
      );
    }

    clic3_memory_free_raw(
      queue_buffered
    );

    cexil_renderer_render_clear(
      &aio_display->renderer
    );

    cexil_renderer_render(
      &aio_display->renderer
    );
  };

  return (
    0x00
  );
}

void aio_display_thread_data_destroy(
  struct aio_display_thread_data* aio_display_thread_data
) {
  clic3_memory_free_raw(
    aio_display_thread_data->queue
  );

  pthread_mutex_destroy(
    &aio_display_thread_data->mutex_render
  );

  pthread_mutex_destroy(
    &aio_display_thread_data->mutex_queue
  );
}
