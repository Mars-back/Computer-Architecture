#!/bin/bash

n=${1:-5}

top -b -n 1 > top.txt
head -n "$n" top.txt > temp.txt
mv temp.txt top.txt
