#include <ao_parameters.h>

#include <clic3.h>

int ao_parameters_parse(
  struct ao_parameters* ao_parameters,
  int length_parameters,
  char** parameters
) {
  ao_parameters->block = 0;
  ao_parameters->export = 0;
  ao_parameters->help = 0;
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
    int index_parameter_valid = clic3_char_arrays_within(
      parameters[index_parameter],
      16,
      "-o",
      "-e",
      "--export",
      "--play",
      "-v",
      "--visualizer",
      "-s",
      "--speed",
      "-b",
      "--block",
      "-x",
      "--synchronize-oscillator",
      "-a",
      "--visualizer-average",
      "-h",
      "--help"
    );

    if (
      index_parameter_valid == -1
    ) {
      return index_parameter;
    } else if (
      index_parameter_valid >= 0 &&
      index_parameter_valid <= 2
    ) {
      ao_parameters->export = 1;

      index_parameter = (
        index_parameter + 1
      );

      if (
        index_parameter >= length_parameters
      ) {
        return -2 - index_parameter;
      }

      ao_parameters->path_export = parameters[index_parameter];
    } else if (
      index_parameter_valid == 3
    ) {
      ao_parameters->play = 1;
    } else if (
      index_parameter_valid >= 4 &&
      index_parameter_valid <= 5
    ) {
      ao_parameters->visualizer = 1;
    } else if (
      index_parameter_valid >= 6 &&
      index_parameter_valid <= 7 &&
      index_parameter < (length_parameters - 1)
    ) {
      index_parameter = (
        index_parameter + 1
      );

      if (
        index_parameter >= length_parameters
      ) {
        return -2 - index_parameter;
      }

      unsigned char status = clic3_char_array_to_unsigned_long_int(
        parameters[
          index_parameter
        ],
        &ao_parameters->speed
      );

      if (
        status != 0 ||
        ao_parameters->speed < 1
      ) {
        return (
          length_parameters +
          index_parameter -
          1
        );
      }
    } else if (
      index_parameter_valid >= 8 &&
      index_parameter_valid <= 9
    ) {
      ao_parameters->block = 1;
    } else if (
      index_parameter_valid >= 10 &&
      index_parameter_valid <= 11
    ) {
      ao_parameters->synced_oscillator = 1;
    } else if (
      index_parameter_valid >= 12 &&
      index_parameter_valid <= 13
    ) {
      ao_parameters->visualizer_average = 1;
    } else if (
      index_parameter_valid >= 14 &&
      index_parameter_valid <= 15
    ) {
      ao_parameters->help = 1;
    }
  }

  return -1;
}
