#include <aio_export.h>
#include <aio_data.h>
#include <aio_frequency.h>

#include <interrupt_handler.h>

#include <stdio.h>

int aio_export_write(
  FILE* file_export,
  float frequency
) {
  signed int status_write = fprintf(
    file_export,
    "%f,",
    frequency
  );

  return status_write;
}

void aio_export_data(
  struct aio_data* aio_data
) {
  pthread_mutex_lock(
    &mutex_exporting
  );

  while (
    (
      aio_data->index_file_input <
      aio_data->length_file_inputs
    ) &&
    (
      interrupt_handler_interrupted ==
      0x00
    )
  ) {
    while(
      !feof(
        aio_data->file_inputs[
          aio_data->index_file_input
        ]
      )
    ) {
      aio_frequency_get(
        aio_data
      );

      int status_write = aio_export_write(
        aio_data->file_output,
        aio_data->frequency
      );

      if (
        status_write < 0
      ) {
        fprintf(
          stderr,
          "error_writing_to_output_file->{%s};\n",
          aio_data->path_export
        );

        aio_data->index_file_input = (
          aio_data->length_file_inputs - 1
        );

        break;
      }
    }

    aio_data->index_file_input = (
      aio_data->index_file_input + 1
    );
  }

  pthread_mutex_unlock(
    &mutex_exporting
  );
}
