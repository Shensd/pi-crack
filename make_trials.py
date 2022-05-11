import random
import hashlib

def md5(data):
    return hashlib.md5(data.encode('utf-8')).hexdigest()

def output_pass_line(hashes_dir, trial, out, word):
    out.write(f"\"{md5(word)}\", // {word}\n")
    with open(f"{hashes_dir}/{trial}", "a") as out_hashes:
        out_hashes.write(f"{md5(word)}\n")

def gen_singles(hashes_dir, out_h, out_c, wordlist):
    
    single_trials = 32

    out_h.write(f"""#define NUM_SINGLE_TRIALS {single_trials}
char* single_trial_hashes[NUM_SINGLE_TRIALS];

""")

    out_c.write("char* single_trial_hashes[NUM_SINGLE_TRIALS] = {\n")

    for i in range(0, single_trials):
        output_pass_line(hashes_dir, f"single-{i}", out_c, random.choice(wordlist))

    out_c.write("};\n\n")

def gen_multi(hashes_dir, out_h, out_c, wordlist):
    max_trial = 32
    min_trial = 2
    total_trials = max_trial - min_trial

    out_h.write(f"""#define TRIAL_MULTI_MAX_HASHES {max_trial}
#define NUM_MULTI_TRIALS {total_trials}
const char* const multi_trials[];

""")

    out_c.write("const char* const multi_trials[] = {\n")

    for i in range(min_trial, max_trial):
        words = random.choices(wordlist, k=i)
        for word in words:
            output_pass_line(hashes_dir, f"multi-{i}", out_c, word)
        out_c.write("NULL,\n")

    out_c.write("};\n\n")


def main():
    with open("rockyou-mini.txt", "r") as wordlist_raw:
        wordlist = list(map(lambda x: x.strip(), wordlist_raw.readlines()))

        out_h = open("trials.h", "w")
        out_c = open("trials.c", "w")

        hashes_dir = "./hashfiles" 

        out_h.write("""#ifndef TRIALS_H
#define TRIALS_H

#include <stddef.h>
#include <stdint.h>

#include "memory.h" // provides a memset method

""")
        out_c.write("""#include "trials.h"

""")

        gen_singles(hashes_dir, out_h, out_c, wordlist)
        gen_multi(hashes_dir, out_h, out_c, wordlist)

        out_h.write("""
#endif // !TRIALS_H
""")

        out_h.close()
        out_c.close()
        

if __name__ == "__main__":
    main()