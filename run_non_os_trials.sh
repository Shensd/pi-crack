#!/bin/bash

TRIAL_DIR="./hashfiles"

HASHCAT_POTFILE="~/.hashcat/hashcat.potfile"
HASHCAT_BIN="hashcat"

JOHN_POTFILE="~/.john/john.pot"
JOHN_BIN="~/Dev/hack/john-1.9.0-jumbo-1/run/john"

echo "[$(date '+%D %T')]" "starting homebrew..."
TRIAL_DIR=$TRIAL_DIR ./trial_homebrew.sh
echo "[$(date '+%D %T')]" "homebrew finished."
echo "[$(date '+%D %T')]" "starting hashcat..."
TRIAL_DIR=$TRIAL_DIR HASHCAT_POTFILE="$HASHCAT_POTFILE" HASHCAT_BIN="$HASHCAT_BIN" ./trial_hashcat.sh
echo "[$(date '+%D %T')]" "hashcat finished..."
echo "[$(date '+%D %T')]" "starting john..."
TRIAL_DIR=$TRIAL_DIR JOHN_POTFILE="$JOHN_POTFILE" JOHN_BIN="$JOHN_BIN" ./trial_john.sh
echo "[$(date '+%D %T')]" "john finished..."