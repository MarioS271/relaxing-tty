# relaxing-tty

A small C program that turns an idle terminal into a cycling display which alternates
between a clock and random visual animations.


## What it does

The program loops indefinitely through two modes:

1. **Clock**: runs `tty-clock` for a random duration between `CLOCK_MIN_SECS` and `CLOCK_MAX_SECS`
2. **Fun**: picks one of the following at random, runs it, then returns to clock mode:
   - `cmatrix`
   - `sl`
   - `pipes`
   - `cbonsai`

Fun mode programs marked as `lolcat_compat` in `defs.h` have a `LOLCAT_MODE_CHANCE` probability of being piped through `lolcat` for colorized output.

Durations and launch arguments are configured in `constants.h` and `defs.h`.


## Dependencies

The following programs must be in `PATH` at runtime:
- tty-clock
- lolcat
- cmatrix
- sl
- pipes
- cbonsai

These programs are all available via `dpkg` and likely other repos like `AUR` too.


## Arguments

| Argument        | Description                                                                         |
|-----------------|-------------------------------------------------------------------------------------|
| `--help`        | Print usage information and exit                                                    |
| `--fast`        | Cycles through modes faster (default: 10x speed via `FAST_MODE_SPEED_MULTIPLIER`)   |
| `--lolcat-only` | Always pipe compatible fun programs through `lolcat`, ignoring `LOLCAT_MODE_CHANCE` |


## Configuration

`defs.h` contains fun mode program definitions, while `constants.h` contains constants such as weights, mode times, and lolcat chance.
Adjust these to your liking.


## Weights

Fun modes use a weight system to avoid repetition. Each mode starts at `1.0` and adjusts after every pick:

- **Chosen**: weight decreases by `WEIGHT_DROP`
- **Not chosen**: weight increases by `WEIGHT_RISE` (`WEIGHT_DROP / (FUN_COUNT - 1)`)
- All weights are clamped to `[WEIGHT_MIN, 1.0]`

This makes recently shown modes less likely to appear again, while skipped modes gradually become more likely.

| Macro                   | Default                         | Description                                      |
|-------------------------|---------------------------------|--------------------------------------------------|
| `WEIGHT_DROP`           | `0.1`                           | Weight decrease on selection                     |
| `WEIGHT_RISE`           | `WEIGHT_DROP / (FUN_COUNT - 1)` | Weight increase when not selected                |
| `WEIGHT_MIN`            | `0.1`                           | Minimum weight (keeps modes in pool)             |
| `LOLCAT_MODE_CHANCE`    | `0.005`                         | Per-run probability of piping through `lolcat`   |


<br><hr>
This project is licensed under the `GPL-3.0-only` license (see [LICENSE](LICENSE)).