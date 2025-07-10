#include <ao_parameters.h>

#include <clic3.h>

int ao_parameters_parse(
  struct ao_parameters* ao_parameters,
  int length_parameters,
  char** parameters
) {
  ao_parameters->export = 0;
  ao_parameters->play = 0;
  ao_parameters->path_export = (void*)0;
  ao_parameters->visualizer = 0;

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
    } else {
      return index_parameter;
    }
  }

  return -1;
}
