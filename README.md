# relaxing-tty

A small C program that turns an idle terminal into a cycling display which alternates
between a clock and random visual animations.


## What it does

The program loops indefinitely through two modes:

1. **Clock**: runs `tty-clock` for a random duration between `CLOCK_MIN_SECS` and `CLOCK_MAX_SECS`
2. **Fun**: picks one of the following at random, runs it, then returns to clock mode:
- `cmatrix`
- `cacafire`
- `sl`
- `pipes.sh`
    
Durations and launch arguments for each program are configured in `config.h`.


## Dependencies

The following programs must be in `PATH` at runtime:
- tty-clock
- cmatrix
- cacafire
- sl
- pipes


## Configuration

Edit `config.h` before building:

| Macro            | Default                                    | Description                              |
|------------------|--------------------------------------------|------------------------------------------|
| `CLOCK_MIN_SECS` | `60`                                       | Minimum clock display duration (seconds) |
| `CLOCK_MAX_SECS` | `300`                                      | Maximum clock display duration (seconds) |
| `FUN_MIN_SECS`   | `30`                                       | Minimum fun animation duration (seconds) |
| `FUN_MAX_SECS`   | `90`                                       | Maximum fun animation duration (seconds) |
| `CLOCK_ARGS`     | `"tty-clock", "-c", "-C", "4", "-s", NULL` | Arguments passed to tty-clock            |
| `CMATRIX_ARGS`   | `"cmatrix", NULL`                          | Arguments passed to cmatrix              |
| `CACAFIRE_ARGS`  | `"cacafire", NULL`                         | Arguments passed to cacafire             |
| `SL_ARGS`        | `"sl", NULL`                               | Arguments passed to sl                   |
| `PIPES_ARGS`     | `"pipes", NULL`                            | Arguments passes to pipes                |


<br><hr>
This project is licensed under the `GPL-3.0-only` license (see [LICENSE](LICENSE)).