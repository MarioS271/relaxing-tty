/**
 * @file config.h
 *
 * @authors @copyright MarioS271
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

// Min/Max Durations for 
#define CLOCK_MIN_SECS 60
#define CLOCK_MAX_SECS 300

#define FUN_MIN_SECS 30
#define FUN_MAX_SECS 90

// Launch Args for programs
#define CLOCK_ARGS "tty-clock", "-c", "-C", "4", "-s", NULL

#define CMATRIX_ARGS "cmatrix", NULL
#define CACAFIRE_ARGS "cacafire", NULL
#define SL_ARGS "sl", NULL