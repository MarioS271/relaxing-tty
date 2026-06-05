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

`defs.h` contains fun mode definitions, while `constants.h` contains constants such as weights and mode times.
Adjust these to your liking.


## Weights

Fun modes use a weight system to avoid repetition. Each mode starts at `1.0` and adjusts after every pick:

- **Chosen**: weight decreases by `WEIGHT_DROP`
- **Not chosen**: weight increases by `WEIGHT_RISE` (`WEIGHT_DROP / (FUN_COUNT - 1)`)
- All weights are clamped to `[WEIGHT_MIN, 1.0]`

This makes recently shown modes less likely to appear again, while skipped modes gradually become more likely.

| Macro          | Default                         | Description                          |
|----------------|---------------------------------|--------------------------------------|
| `WEIGHT_DROP`  | `0.1`                           | Weight decrease on selection         |
| `WEIGHT_RISE`  | `WEIGHT_DROP / (FUN_COUNT - 1)` | Weight increase when not selected    |
| `WEIGHT_MIN`   | `0.1`                           | Minimum weight (keeps modes in pool) |


<br><hr>
This project is licensed under the `GPL-3.0-only` license (see [LICENSE](LICENSE)).