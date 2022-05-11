#include "mini_uart.h"
#include "printf.h"
#include "time.h"
#include "memory.h"

#include "crack.h"

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

    printf("%d,\"%s\",%d,%d,%d,%d,%d,%d,%s,%s\r\n",
        current_trial++, // trial
        "single", // type
        1, // # hashes
        (result == NULL ? 0 : 1), // # cracked
        words_tested, // # words tested
        start_time, // start time
        end_time, // end time
        end_time - start_time, // delta
        to_crack, // target hash
        result // cracked hash
    );
}

// this function can handle at most 
#define TRIAL_MULTI_MAX_HASHES 64
void trial_multi(uint8_t* hashes, uint32_t num_hashes) {
    char* output[TRIAL_MULTI_MAX_HASHES];

    uint32_t words_tested = 0;
    uint32_t start_time = get_uptime();

    uint32_t result = crack_multi(hashes, num_hashes, output, &words_tested);

    uint32_t end_time = get_uptime();

    printf("%d,\"%s\",%d,%d,%d,%d,%d,%d,,\r\n",
        current_trial++, // trial
        "multi", // type
        num_hashes, // # hashes
        result, // # cracked
        words_tested, // # words tested
        start_time, // start time
        end_time, // end time
        end_time - start_time // delta
        // TODO how output hash
        // TODO how ouput result
    );

    /*
    if(result > 0) {
        for(unsigned int i = 0; i < num_hashes; i++) {
            if(output[i] == NULL) {
                printf("x %s:\r\n", hashstrings[i]);
            } else {
                printf("o %s:%s\r\n", hashstrings[i], output[i]);
            }
        }
        printf("cracked in %d hashes in %d microseconds\t\n", result, delta);
    } else {
        printf("unable to crack, exhausted in %d microseconds\t\n", delta);
    }
    */
}

void kernel_main(void)
{
	uart_init();

    // printf("MD5-CRACK-OS STARTED.\r\n");
    printf("trial,type,\"# hashes\",\"# cracked\",\"# words tested\",\"start time\",\"end time\",delta,hash,password\r\n");

    current_trial = 1;

    /** PERFORM SINGLE HASH TRIALS **/
    // uint8_t single_trial_buffer[16];   
    #define NUM_SINGLE_TRIALS 5
    char* single_trial_hashes[NUM_SINGLE_TRIALS] = {
        "67355e810914ddce4333bc56816705a8", // alexandra12
        "65fbef05e01fac390cb3fa073fb3e8cf", // anthony
        "5f4dcc3b5aa765d61d8327deb882cf99", // password
        "ea5dc6553f4d915abc7579aad7d027d9", // bestpass
        "2ab96390c7dbe3439de74d0c9b0b1767", // hunter2
    };
    
    for(uint32_t i = 0; i < NUM_SINGLE_TRIALS; i++) {
        // from_hex(single_trial_hashes[i], 32, single_trial_buffer, 16);
        trial_single(single_trial_hashes[i]);
    }
    /** END SINGLE HASH TRIALS **/

    // char trial_single_a_raw[] = "67355e810914ddce4333bc56816705a8"; // alexandra12

    // from_hex(trial_single_a_raw, 32, trial_single_a, 16);
    // trial_single(1, trial_single_a);

    // char to_crack[] = "65fbef05e01fac390cb3fa073fb3e8cf"; // anthony
    // char to_crack[] = "67355e810914ddce4333bc56816705a8"; // alexandra12
    
    // uint8_t buffer[16];
    // from_hex(to_crack, sizeof(to_crack), buffer, 16);

/*    
    struct trial_multi_data {
        uint32_t num_hashes;
        char hashes[TRIAL_MULTI_MAX_HASHES][32];
    };

    #define NUM_MULTI_TRIALS 1
    struct trial_multi_data multi_trials[NUM_MULTI_TRIALS] = {
        {
            5,
            {
               "67355e810914ddce4333bc56816705a8", // alexandra12
                "65fbef05e01fac390cb3fa073fb3e8cf", // anthony
                "5f4dcc3b5aa765d61d8327deb882cf99", // password
                "ea5dc6553f4d915abc7579aad7d027d9", // bestpass
                "2ab96390c7dbe3439de74d0c9b0b1767", // hunter2 
            }
        }
    };

    for(unsigned int i = 0; i < NUM_MULTI_TRIALS; i++) {
        printf("%s\r\n", multi_trials[i].hashes[0]);
    }
*/

    /*
    #define NUM_HASHES 5
    char* hashstrings[NUM_HASHES] = {
        "67355e810914ddce4333bc56816705a8", // alexandra12
        "65fbef05e01fac390cb3fa073fb3e8cf", // anthony
        "5f4dcc3b5aa765d61d8327deb882cf99", // password
        "ea5dc6553f4d915abc7579aad7d027d9", // bestpass
        "2ab96390c7dbe3439de74d0c9b0b1767", // hunter2
    };
    */
    #define NUM_MULTI_TRIALS 2
    const char* const multi_trials[] = {
        "67355e810914ddce4333bc56816705a8", // alexandra12
        "65fbef05e01fac390cb3fa073fb3e8cf", // anthony
        "5f4dcc3b5aa765d61d8327deb882cf99", // password
        "ea5dc6553f4d915abc7579aad7d027d9", // bestpass
        "2ab96390c7dbe3439de74d0c9b0b1767", // hunter2
        NULL,
        "67355e810914ddce4333bc56816705a8", // alexandra12
        "65fbef05e01fac390cb3fa073fb3e8cf", // anthony
        "2ab96390c7dbe3439de74d0c9b0b1767", // hunter2
        NULL,
    };
    uint8_t hashes[TRIAL_MULTI_MAX_HASHES][16];
    // char* output[NUM_HASHES];
    /*
    for(unsigned int i = 0; i < NUM_HASHES; i++) {
        from_hex(hashstrings[i], 32, hashes[i], 16);
    }
    */
    /*
    for(unsigned int trial = 0; trial < NUM_MULTI_TRIALS; trial++) {
        unsigned int current_trial_num_hashes = 0;
        for(unsigned int i = 0; i < TRIAL_MULTI_MAX_HASHES; i++) {
            if(multi_trials[trial][i] == NULL) break;
            current_trial_num_hashes++;
        }

        trial_multi(hashes, current_trial_num_hashes);

        trial++;
    }
    */

    // this is the scariest block of code in this project and i refuse 
    // to explain what it does and how
    uint32_t trial_block_index = 0;
    for(unsigned int trial = 0; trial < NUM_MULTI_TRIALS; trial++) {
        unsigned int current_trial_num_hashes = 0;
        for(unsigned int i = trial_block_index; i < 512; i++) {
            if(multi_trials[i] == NULL) break;
            current_trial_num_hashes++;
        }

        for(unsigned int i = trial_block_index; i < current_trial_num_hashes; i++) {
            from_hex(multi_trials[i], 32, hashes[i], 16);
        }

        trial_multi(hashes, current_trial_num_hashes);

        trial_block_index += current_trial_num_hashes + 1;
    }

    // uint32_t last_time = get_uptime();

    // char* result = crack(buffer);
    // uint32_t result = crack_multi(hashes[0], NUM_HASHES, output);

    // uint32_t delta = get_uptime() - last_time;

    /*
    if(result) {
        printf("%s:%s\n", to_crack, result);
        printf("cracked in %d microseconds\t\n", delta);
    } else {
        // printf("%s:\n", to_crack);
        printf("unable to crack, exhausted in %d microseconds\t\n", delta);
    }
    */
    
    /*
    if(result > 0) {
        for(unsigned int i = 0; i < NUM_HASHES; i++) {
            if(output[i] == NULL) {
                printf("x %s:\r\n", hashstrings[i]);
            } else {
                printf("o %s:%s\r\n", hashstrings[i], output[i]);
            }
        }
        printf("cracked in %d hashes in %d microseconds\t\n", result, delta);
    } else {
        printf("unable to crack, exhausted in %d microseconds\t\n", delta);
    }
    */
    

    while(1) {}
}
