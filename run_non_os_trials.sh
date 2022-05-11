#!/bin/bash

TRIAL_DIR="./hashfiles"

HASHCAT_POTFILE="~/.hashcat/hashcat.potfile"
HASHCAT_BIN="hashcat"

JOHN_POTFILE="~/.john/john.pot"
JOHN_BIN="~/Dev/hack/john-1.9.0-jumbo-1/run/john"

# homebrew crack program
TRIAL_CSV="homebrew.csv"
trial=0
echo "trial,type,\"# hashes\",\"# cracked\",\"# words tested\",\"start time\",\"end time\",delta,target" >> $TRIAL_CSV
for i in ${TRIAL_DIR}/*; do
    ### DO ANY PRE_TIMER STUFF HERE ###
    
    ### ^^^ YEAH RIGHT THERE ###
    n_hashes=$(echo $i | cut -d'-' -f2); 
    trial_type=$(echo $i | rev | cut -d'/' -f1 | rev | cut -d'-' -f1);
    start=`date +%s%N`; 
    ### CHANGE COMMAND HERE ###

    homebrew/homebrew "$i" > /dev/null

    ### ^^^^ THAT ONE BAYBEEE ###
    end=`date +%s%N`; 
    printf "%d,\"%s\",%d,%d,%d,%d,%d,%d" $trial $trial_type $n_hashes $n_hashes $start $end $(expr \( $end - $start \) / 1000) >> $TRIAL_CSV;
    if [ $trial_type == "single" ]; then
        printf ",%s" $(head -n 1 $i) >> $TRIAL_CSV
    fi
    echo >> $TRIAL_CSV
    trial=$(echo "${trial}+1" | bc);
done;

# hashcat
TRIAL_CSV="hashcat.csv"
trial=0
echo "trial,type,\"# hashes\",\"# cracked\",\"# words tested\",\"start time\",\"end time\",delta,target" >> $TRIAL_CSV
for i in ${TRIAL_DIR}/*; do
    ### DO ANY PRE_TIMER STUFF HERE ###

    rm HASHCAT_POTFILE; # remove potfile so it doesnt infect runs

    ### ^^^ YEAH RIGHT THERE ###
    n_hashes=$(echo $i | cut -d'-' -f2); 
    trial_type=$(echo $i | rev | cut -d'/' -f1 | rev | cut -d'-' -f1);
    start=`date +%s%N`; 
    ### CHANGE COMMAND HERE ###

    $HASHCAT_BIN --cpu-affinity 1 -m 0 -d 1 -a 0 $i rockyou-mini.txt 2>&1 > /dev/null; 

    ### ^^^^ THAT ONE BAYBEEE ###
    end=`date +%s%N`; 
    printf "%d,\"%s\",%d,%d,%d,%d,%d,%d" $trial $trial_type $n_hashes $n_hashes $start $end $(expr \( $end - $start \) / 1000) >> $TRIAL_CSV;
    if [ $trial_type == "single" ]; then
        printf ",%s" $(head -n 1 $i) >> $TRIAL_CSV
    fi
    echo >> $TRIAL_CSV
    trial=$(echo "${trial}+1" | bc);
done;

# john
TRIAL_CSV="john.csv"
trial=0
echo "trial,type,\"# hashes\",\"# cracked\",\"# words tested\",\"start time\",\"end time\",delta,target" >> $TRIAL_CSV
for i in ${TRIAL_DIR}/*; do
    ### DO ANY PRE_TIMER STUFF HERE ###

    # THIS WILL LIKELY BE DIFFERENT ON DIFFERENT SYSTEMS
    rm $JOHN_POTFILE; # remove potfile so it doesnt infect runs

    ### ^^^ YEAH RIGHT THERE ###
    n_hashes=$(echo $i | cut -d'-' -f2); 
    trial_type=$(echo $i | rev | cut -d'/' -f1 | rev | cut -d'-' -f1);
    start=`date +%s%N`; 
    ### CHANGE COMMAND HERE ###

    $JOHN_BIN --format=Raw-MD5 --wordlist=rockyou-mini.txt $i 2>&1 > /dev/null; 

    ### ^^^^ THAT ONE BAYBEEE ###
    end=`date +%s%N`; 
    printf "%d,\"%s\",%d,%d,%d,%d,%d,%d" $trial $trial_type $n_hashes $n_hashes $start $end $(expr \( $end - $start \) / 1000) >> $TRIAL_CSV;
    if [ $trial_type == "single" ]; then
        printf ",%s" $(head -n 1 $i) >> $TRIAL_CSV
    fi
    echo >> $TRIAL_CSV
    trial=$(echo "${trial}+1" | bc);
done;