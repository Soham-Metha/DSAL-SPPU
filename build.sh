#!/bin/bash

cpp_prefix=proj
txt_prefix=testdata

clear &&
g++ $cpp_prefix$1.cpp -o $cpp_prefix$1.out

./$cpp_prefix$1.out $2 < $txt_prefix$1.txt > output$1

rm ./*.out
