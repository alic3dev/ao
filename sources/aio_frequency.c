#include <aio_frequency.h>
#include <aio_data.h>

void aio_frequency_get(
  struct aio_data* aio_data,
  unsigned int index_file_input
) {
  unsigned char byte_file_input = getc(
    aio_data->file_inputs[index_file_input]
  );

  unsigned int index_note = (
    byte_file_input % aio_data->length_note_table
  );

  aio_data->frequency = aio_data->note_table[
    index_note
  ];
}

