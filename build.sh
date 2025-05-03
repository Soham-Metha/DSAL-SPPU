#!/bin/bash
#file name prefix
prefix=proj

clear &&
#build object file
g++ $prefix$1.cpp -o $prefix$1.out

#run executable
./$prefix$1.out $2

#clean the trash
rm ./*.out
