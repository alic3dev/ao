#include <ao_parameters.h>

#include <clic3.h>

int ao_parameters_parse(
  struct ao_parameters* ao_parameters,
  int length_parameters,
  char** parameters
) {
  ao_parameters->block = 0;
  ao_parameters->export = 0;
  ao_parameters->play = 0;
  ao_parameters->path_export = (void*)0;
  ao_parameters->speed = 1;
  ao_parameters->synced_oscillator = 0;
  ao_parameters->visualizer = 0;
  ao_parameters->visualizer_average = 0;

  for (
    unsigned int index_parameter = 1;
    index_parameter < length_parameters;
    ++index_parameter
  ) {
    if (
      clic3_char_arrays_within(
        parameters[index_parameter],
        3,
        "-o",
        "-e",
        "--export"
      ) != -1
    ) {
      ao_parameters->export = 1;

      index_parameter = (
        index_parameter + 1
      );

      if (
        index_parameter >= length_parameters
      ) {
        return -1;
      }

      ao_parameters->path_export = parameters[index_parameter];
    } else if (
      clic3_char_arrays_within(
        parameters[index_parameter],
        1,
        "--play"
      ) != -1
    ) {
      ao_parameters->play = 1;
    } else if (
      clic3_char_arrays_within(
        parameters[index_parameter],
        2,
        "-v",
        "--visualizer"
      ) != -1
    ) {
      ao_parameters->visualizer = 1;
    } else if (
      clic3_char_arrays_within(
        parameters[index_parameter],
        2,
        "-s",
        "--speed"
      ) != -1 &&
      index_parameter < (length_parameters - 1)
    ) {
      index_parameter = (
        index_parameter + 1
      );

      unsigned char status = clic3_char_array_to_unsigned_long_int(
        parameters[index_parameter],
        &ao_parameters->speed
      );

      if (
        status != 0 ||
        ao_parameters->speed < 1
      ) {
        return -1;
      }
    } else if (
      clic3_char_arrays_within(
        parameters[index_parameter],
        2,
        "-b",
        "--block"
      ) != -1
    ) {
      ao_parameters->block = 1;
    } else if (
      clic3_char_arrays_within(
        parameters[index_parameter],
        2,
        "-x",
        "--synchronize-oscillator"
      ) != -1
    ) {
      ao_parameters->synced_oscillator = 1;
    } else if (
      clic3_char_arrays_within(
        parameters[index_parameter],
        2,
        "-a",
        "--visualizer-average"
      ) != -1
    ) {
      ao_parameters->visualizer_average = 1;
    } else {
      return index_parameter;
    }
  }

  return -1;
}
