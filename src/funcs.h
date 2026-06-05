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
void cleanup();
void set_title();
void run_timed(char* const argv[], int seconds);
void run_until_exit(char* const argv[]);