#!/bin/bash
#file name cpp_prefix
cpp_prefix=proj
txt_prefix=testdata
clear &&
#build object file
g++ $cpp_prefix$1.cpp -o $cpp_prefix$1.out

#run executable
./$cpp_prefix$1.out $2 < $txt_prefix$1.txt

#clean the trash
rm ./*.out
