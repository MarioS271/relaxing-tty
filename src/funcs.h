/**
 * @file funcs.h
 * @authors MarioS271
 * 
 * SPDX-FileCopyrightText: (C) MarioS271 2026
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

#include <stdlib.h>

int rand_range(int min, int max);
void validate_progs();
pid_t spawn(char* const argv[]);
void spawn_piped(char* const argv_prog[], volatile pid_t* pid_proc, volatile pid_t* pid_lolcat);
void cleanup();
void set_title();
void run_timed(char* const argv[], bool lolcat_mode, int seconds);
void run_until_exit(char* const argv[], bool lolcat_mode);