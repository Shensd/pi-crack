#!/bin/bash

rm hashfiles -r
mkdir hashfiles
python3 make_trials.py
mv trials.c src/trials.c
mv trials.h include/trials.h