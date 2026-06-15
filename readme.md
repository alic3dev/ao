# ao

send files to audio output on a loop

## usage

```
usage: ao [?parameters] [...paths_to_file_inputs]
parameters:
  -o, -e, --export [output_path] : exports to a file
    --play                       : plays audio while exporting (default is no audio output when exporting)
  -b, --block                    : ceils and floors to maximum and minimum values
  --octave-minimum [#]           : sets the minimum octave
  --octave-maximum [#]           : sets the maximum octave
  -s, --speed [#1+]              : the speed of file playback
  -x, --synchronize_oscillator   : synchronizes oscillators to the speed value
  -v, --visualizer               : displays an audio graph of the output
  -a, --visualize_average        : averages the display output
  -h, --help                     : displays usage information
```

## dependencies

### os

- mac_os: 10.5+

### libraries

- [alic3dev](https://github.com/alic3dev)
- - [`cer0`](https://github.com/alic3dev/cer0)
- - [`cexil`](https://github.com/alic3dev/cexil)
- - [`clic3`](https://github.com/alic3dev/clic3)
- - [`interrupt_handler`](https://github.com/alic3dev/interrupt_handler)
- - [`math_c`](https://github.com/alic3dev/math_c)

## build

```zsh
make
```

## clean

```zsh
make clean
```

## copyright|copyleft

> © [copyright|copyleft]:alic3dev(2025|2026)->{all_lefts_reserved|all_rights_reserved};
