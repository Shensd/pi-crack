#include "mini_uart.h"
#include "printf.h"
#include "time.h"
#include "memory.h"

#include "crack.h"

#include "trials.h"

#include <stddef.h>
#include <stdint.h>

extern unsigned char bss_end;

uint32_t current_trial;

void trial_single(char* to_crack) {
    uint8_t buffer[16];

    from_hex(to_crack, 32, buffer, 16);

    uint32_t words_tested = 0;
    uint32_t start_time = get_uptime();

    char* result = crack(buffer, &words_tested);

    uint32_t end_time = get_uptime();

    printf("%u,\"%s\",%u,%u,%u,%u,%u,%u,%s\r\n",
        current_trial++, // trial
        "single", // type
        1, // # hashes
        (result == NULL ? 0 : 1), // # cracked
        words_tested, // # words tested
        start_time, // start time
        end_time, // end time
        (uint64_t) end_time - start_time, // delta
        to_crack // target hash
        // result // cracked hash
    );
}


void trial_multi(uint8_t* hashes, uint32_t num_hashes) {
    char* output[TRIAL_MULTI_MAX_HASHES];

    uint32_t words_tested = 0;
    uint32_t start_time = get_uptime();

    uint32_t result = crack_multi(hashes, num_hashes, output, &words_tested);

    uint32_t end_time = get_uptime();

    printf("%u,\"%s\",%u,%u,%u,%u,%u,%u,\r\n",
        current_trial++, // trial
        "multi", // type
        num_hashes, // # hashes
        result, // # cracked
        words_tested, // # words tested
        start_time, // start time
        end_time, // end time
        end_time - start_time // delta
        // TODO how output hashes
        // TODO how ouput result
    );
}

void kernel_main(void)
{
	uart_init();

    // printf("MD5-CRACK-OS STARTED.\r\n");
    printf("trial,type,\"# hashes\",\"# cracked\",\"# words tested\",\"start time\",\"end time\",delta,target\r\n");

    current_trial = 0;
    
    for(uint32_t i = 0; i < NUM_SINGLE_TRIALS; i++) {
        trial_single(single_trial_hashes[i]);
    }
 
    // bufferspace for converted hashes
    uint8_t hashes[TRIAL_MULTI_MAX_HASHES][16];

    // this is the scariest block of code in this project and i refuse 
    // to explain what it does and how
    uint32_t trial_block_index = 0;
    for(unsigned int trial = 0; trial < NUM_MULTI_TRIALS; trial++) {
        unsigned int current_trial_num_hashes = 0;
        for(unsigned int i = trial_block_index; i < TOTAL_MULTI_TRIAL_MEMBERS; i++) {
            if(multi_trials[i] == NULL) break;
            current_trial_num_hashes++;
        }

        for(unsigned int i = 0; i < current_trial_num_hashes; i++) {
            // printf("%d %s\n", trial_block_index, multi_trials[trial_block_index+i]);
            from_hex(multi_trials[trial_block_index+i], 32, hashes[i], 16);
        }

        trial_multi(hashes, current_trial_num_hashes);

        trial_block_index += current_trial_num_hashes + 1;
    }

    while(1) {}
}
