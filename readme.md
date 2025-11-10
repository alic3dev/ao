# ao

send files to audio output on a loop

## usage

```
usage: ao [?parameters] [...paths_to_file_inputs]
parameters:
  -o, -e, --export [output_path]
    --play : plays audio while exporting (default is no audio output when exporting)
  -b, --block : ceils and floors to maximum and minimum values
  -s, --speed [#1+] : the speed of file playback
  -x, --synchronize-oscillator : synchronizes oscillators to the speed value
  -v, --visualizer : displays an audio graph of the output
  -a, --visualize-average : averages the display output
  --help : displays usage information
```

## dependencies

### os

- mac_os: 10.5+

### libraries

- [cer0](https://github.com/alic3dev/cer0)
- [cexil](https://github.com/alic3dev/cexil)
- [clic3](https://github.com/alic3dev/clic3)

## build

```zsh
make
```

## clean

```zsh
make clean
```

## copyleft|copyright

> copy_right_copy_left:alic3dev[2025]\_all_rights_reserved_all_lefts_reserved
