#!/bin/sh
g++ $1 -I ./googletest/googletest/include/ -lgtest -L. -std=c++14 -pthread -fsanitize=address
