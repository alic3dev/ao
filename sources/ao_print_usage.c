#include <ao_print_usage.h>

#include <stdio.h>

void ao_print_usage(
  unsigned char to_error_stream
) {
  FILE* stream_output = (
    (
      to_error_stream ==
      0x00
    )
    ? stdout
    : stderr
  );

  fprintf(
    stream_output,
    "usage: ao [?parameters] [...paths_to_file_inputs]\n"
    "parameters:\n"
    "  -o, -e, --export [output_path] : exports to a file\n"
    "    --play                       : plays audio while exporting (default is no audio output when exporting)\n"
    "  -b, --block                    : ceils and floors to maximum and minimum values\n"
    "  --octave-minimum [#]           : sets the minimum octave\n"
    "  --octave-maximum [#]           : sets the maximum octave\n"
    "  -s, --speed [#1+]              : the speed of file playback\n"
    "  -x, --synchronize_oscillator   : synchronizes oscillators to the speed value\n"
    "  -v, --visualizer               : displays an audio graph of the output\n"
    "  -a, --visualize_average        : averages the display output\n"
    "  -h, --help                     : displays usage information\n"
  );
}
