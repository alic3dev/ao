#include <ao.h>
#include <aio.h>
#include <aio_data.h>

#include <cer0.h>

#include <stdio.h>

int main(
  int count_parameters,
  char** parameters
) {
  if (count_parameters != 2) {
    fprintf(
      stderr,
      "usage: ao path_file_input\n"
    );

    return 1;
  }

  struct aio_data aio_data;
  aio_data.initialized = 0;

  aio_data.length_file_inputs = (
    count_parameters - 1
  );

  aio_data.file_inputs = malloc(
    sizeof(FILE*) * 
    aio_data.length_file_inputs
  );

  for (
    unsigned int index_file_input = 0;
    index_file_input < aio_data.length_file_inputs;
    ++index_file_input
  ) {
    aio_data.file_inputs[index_file_input] = fopen(
      parameters[
        index_file_input + 1
      ],
      "rb"
    );

    if (!aio_data.file_inputs[index_file_input]) {
      fprintf(
        stderr,
        "unable_to_open:%s\n",
        parameters[1]
      );

      for (
        unsigned int index_file_input_previous = 0;
        index_file_input_previous < index_file_input;
        ++index_file_input_previous
      ) {
        fclose(
          aio_data.file_inputs[
            index_file_input_previous
          ]
        );
      }

      return 2;
    }
  }

  aio_data.note_table = cer0_note_table_create(
    0,
    12,
    cer0_frequency_root_standard
  );

  aio_data.length_note_table = cer0_note_table_length(
    0,
    12
  );

  struct cer0_audio_output output_audio;
  cer0_audio_output_initialize(
    &output_audio,
    aio,
    &aio_data
  );

  cer0_oscillator_initialize(
    &aio_data.oscillator,
    output_audio.sample_rate,
    0.0f,
    sine
  );

  aio_data.initialized = 1;

  printf("press enter to quit:");
  getc(stdin);
  
  for (
    unsigned int index_file_input = 0;
    index_file_input < aio_data.length_file_inputs;
    ++index_file_input
  ) {
    fclose(
      aio_data.file_inputs[
        index_file_input
       ]
    );
  }

  free(aio_data.file_inputs);
  free(aio_data.note_table);

  cer0_audio_output_destroy(
    &output_audio
  );

  return 0;
}
