#include <aio_export.h>
#include <aio_data.h>
#include <aio_frequency.h>

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

  for (
    unsigned int index_file_input = 0;
    index_file_input < aio_data->length_file_inputs;
    ++index_file_input
  ) {
    do {
      aio_frequency_get(
        aio_data,
        index_file_input
      );

      int status_write = aio_export_write(
        aio_data->file_output,
        aio_data->frequency
      );

      if (status_write < 0) {
        fprintf(
          stderr,
          "error_writing_to_output_file->{%s};\n",
          aio_data->path_export
        );

        index_file_input = aio_data->length_file_inputs;

        break;
      }
    } while(
      !feof(
        aio_data->file_inputs[index_file_input]
      )
    );
  }

  pthread_mutex_unlock(
    &mutex_exporting
  );
}
