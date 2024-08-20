#!/bin/sh
g++ $1 -I ./googletest/googletest/include/ -lgtest -L. -std=c++20 -pthread -fsanitize=address
