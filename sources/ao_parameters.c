#include <ao_parameters.h>

#include <clic3_char_arrays.h>

int ao_parameters_parse(
  struct ao_parameters* ao_parameters,
  int length_parameters,
  char** parameters
) {
  ao_parameters->block = (
    0x00
  );

  ao_parameters->export = (
    0x00
  );

  ao_parameters->help = (
    0x00
  );

  ao_parameters->octave_minimum = (
    0x00
  );

  ao_parameters->octave_maximum = (
    0x0c
  );

  ao_parameters->play = (
    0x00
  );

  ao_parameters->path_export = (
    0x00
  );

  ao_parameters->speed = (
    0x01
  );

  ao_parameters->synced_oscillator = (
    0x00
  );

  ao_parameters->visualizer = (
    0x00
  );

  ao_parameters->visualizer_average = (
    0x00
  );

  if (
    (
      length_parameters ==
      0x02
    ) &&
    clic3_char_arrays_within(
      parameters[
        0x01
      ],
      0x02,
      "-h",
      "--help"
    ) !=
    -0x01
  ) {
    ao_parameters->help = (
      0x01
    );

    return (
      0x00
    );
  }

  for (
    unsigned int index_parameter = (
      0x01
    );
    (
      index_parameter <
      (
        length_parameters -
        0x01
      )
    );
    ++index_parameter
  ) {
    int index_parameter_valid = (
      clic3_char_arrays_within(
        parameters[
          index_parameter
        ],
        0x12,
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
        "--help",
        "--octave-minimum",
        "--octave-maximum"
      )
    );

    if (
      index_parameter_valid ==
      -0x01
    ) {
      return (
        index_parameter
      );
    } else if (
      (
        index_parameter_valid >=
        0x00
      ) &&
      (
        index_parameter_valid <=
        0x02
      ) &&
      (
        index_parameter <
        (
          length_parameters -
          0x01
        )
      )
    ) {
      ao_parameters->export = (
        0x01
      );

      index_parameter = (
        index_parameter +
        0x01
      );

      ao_parameters->path_export = (
        parameters[
          index_parameter
        ]
      );
    } else if (
      index_parameter_valid ==
      0x03
    ) {
      ao_parameters->play = (
        0x01
      );
    } else if (
      (
        index_parameter_valid >=
        0x04
      ) &&
      (
        index_parameter_valid <=
        0x05
      )
    ) {
      ao_parameters->visualizer = (
        0x01
      );
    } else if (
      (
        index_parameter_valid >=
        0x06
      ) &&
      (
        index_parameter_valid <=
        0x07
      ) &&
      (
        index_parameter <
        (
          length_parameters -
          0x01
        )
      )
    ) {
      index_parameter = (
        index_parameter +
        0x01
      );

      unsigned char status = (
        clic3_char_array_to_unsigned_long_int(
          parameters[
            index_parameter
          ],
          &ao_parameters->speed
        )
      );

      if (
        (
          status !=
          0x00
        ) ||
        (
          ao_parameters->speed <
          0x01
        )
      ) {
        return (
          length_parameters +
          index_parameter -
          0x01
        );
      }
    } else if (
      (
        index_parameter_valid >=
        0x08
      ) &&
      (
        index_parameter_valid <=
        0x09
      )
    ) {
      ao_parameters->block = (
        0x01
      );
    } else if (
      (
        index_parameter_valid >=
        0x0a
      ) &&
      (
        index_parameter_valid <=
        0x0b
      )
    ) {
      ao_parameters->synced_oscillator = (
        0x01
      );
    } else if (
      (
        index_parameter_valid >=
        0x0c
      ) &&
      (
        index_parameter_valid <=
        0x0d
      )
    ) {
      ao_parameters->visualizer_average = (
        0x01
      );
    } else if (
      (
        index_parameter_valid >=
        0x0e
      ) &&
      (
        index_parameter_valid <=
        0x0f
      )
    ) {
      ao_parameters->help = (
        0x01
      );
    } else if (
      (
        index_parameter_valid ==
        0x10
      ) ||
      (
        index_parameter_valid ==
        0x11
      )
    ) {
      int value;

      index_parameter = (
        index_parameter +
        0x01
      );

      unsigned char status = (
        clic3_char_array_to_int(
          parameters[
            index_parameter
          ],
          &value
        )
      );

      if (
        (
          status !=
          0x00
        ) ||
        (
          value <
          -0x7f
        ) ||
        (
          value >
          0x7f
        )
      ) {
        return (
          length_parameters +
          index_parameter -
          0x01
        );
      }

      if (
        index_parameter_valid ==
        0x10
      ) {
        ao_parameters->octave_minimum = (
          value
        );
      } else {
        ao_parameters->octave_maximum = (
          value
        );
      }
    }
  }

  if (
    ao_parameters->octave_minimum >
    ao_parameters->octave_maximum
  ) {
    char octave_hold = (
      ao_parameters->octave_minimum
    );

    ao_parameters->octave_minimum = (
      ao_parameters->octave_maximum
    );

    ao_parameters->octave_maximum = (
      octave_hold
    );
  }

  return (
    length_parameters -
    0x01
  );
}
