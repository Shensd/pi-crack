#!/bin/bash

TRIAL_CSV="homebrew.csv"
trial=0
echo "trial,type,\"# hashes\",\"# cracked\",\"# words tested\",\"start time\",\"end time\",delta,target" >> $TRIAL_CSV
for i in ${TRIAL_DIR}/*; do
    ### DO ANY PRE_TIMER STUFF HERE ###
    
    ### ^^^ YEAH RIGHT THERE ###
    n_hashes=$(echo $i | cut -d'-' -f2); 
    trial_type=$(echo $i | rev | cut -d'/' -f1 | rev | cut -d'-' -f1);
    if [ $trial_type == "single" ]; then
        n_hashes="1"
    fi
    start=`date +%s%N`; 
    ### CHANGE COMMAND HERE ###

    ./homebrew/homebrew "$i" > /dev/null

    ### ^^^^ THAT ONE BAYBEEE ###
    end=`date +%s%N`; 
    printf "%d,\"%s\",%d,%d,%d,%d,%d,%d" $trial $trial_type $n_hashes $n_hashes 0 $(expr $start / 1000) $(expr $end / 1000) $(expr \( $end - $start \) / 1000) >> $TRIAL_CSV;
    if [ $trial_type == "single" ]; then
        printf ",%s" $(head -n 1 $i) >> $TRIAL_CSV
    fi
    echo >> $TRIAL_CSV
    trial=$(echo "${trial}+1" | bc);
done;