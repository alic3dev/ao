#include <ao.h>
#include <ao_parameters.h>
#include <ao_print_usage.h>
#include <aio_export.h>
#include <aio.h>
#include <aio_data.h>
#include <aio_display.h>

#include <cer0.h>

#include <stdio.h>

int main(
  int count_parameters,
  char** parameters
) {
  if (count_parameters < 2) {
    ao_print_usage(1);

    return 1;
  }

  struct ao_parameters ao_parameters;

  int index_parameters_input = ao_parameters_parse(
    &ao_parameters,
    count_parameters,
    parameters
  );

  if (index_parameters_input == -1) {
    ao_print_usage(1);

    return 2;
  }
  
  struct aio_data aio_data;
  aio_data.initialized = 0;

  aio_data.mode = ao_parameters.export == 1 ? (
    ao_parameters.play == 1 ? export_play : export
  ) : play;
  
  if (
    aio_data.mode == export ||
    aio_data.mode == export_play
  ) {
    aio_data.file_output = fopen(
      ao_parameters.path_export,
      "wb"
    );

    aio_data.exporting = 1;
  }

  aio_data.visualizer = ao_parameters.visualizer;

  aio_data.length_file_inputs = (
    count_parameters - index_parameters_input
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
        index_file_input + index_parameters_input
      ],
      "rb"
    );

    if (!aio_data.file_inputs[index_file_input]) {
      fprintf(
        stderr,
        "unable_to_open:%s\n",
        parameters[
          index_file_input + index_parameters_input
        ]
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

  pthread_mutex_init(
    &mutex_exporting,
    (void*)0
  );

  pthread_mutex_init(
    &mutex_export_write,
    (void*)0
  );

  if (
    aio_data.mode == export_play ||
    aio_data.mode == play
  ) {
    if (aio_data.visualizer != 0) {
      aio_display_initialize(
        &aio_data.display
      );
    }

    pthread_mutex_lock(
      &mutex_exporting
    );

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
  } else if (
    aio_data.mode == export
  ) {
    aio_export_data(
      &aio_data
    );
  }

  pthread_mutex_lock(
    &mutex_exporting
  );

  if (
    aio_data.mode == export_play ||
    aio_data.mode == play
  ) {
    cer0_audio_output_destroy(
      &output_audio
    );
  }

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

  aio_display_destroy(
    &aio_data.display
  );

  return 0;
}
