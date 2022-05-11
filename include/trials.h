#ifndef TRIALS_H
#define TRIALS_H

#include <stddef.h>
#include <stdint.h>

#include "memory.h" // provides a memset method

#define NUM_SINGLE_TRIALS 32
char* single_trial_hashes[NUM_SINGLE_TRIALS];

#define TRIAL_MULTI_MAX_HASHES 32
#define NUM_MULTI_TRIALS 30
const char* const multi_trials[];


#endif // !TRIALS_H
