#!/bin/sh
# -fsanitize=address
g++ $1 \
-I ./googletest/googletest/include/ \
-I ./googletest/googlemock/include/ \
-lgtest -L. -std=c++20 -pthread
