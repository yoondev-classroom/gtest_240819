# Google Test

```sh
# gtest-all.cc
$ g++ -c -std=c++14 -O2 ./googletest/googletest/src/gtest-all.cc \
-I ./googletest/googletest/include \
-I ./googletest/googletest

# gmock-all.cc
$ g++ -c -std=c++14 -O2 ./googletest/googlemock/src/gmock-all.cc \
-I ./googletest/googlemock/include \
-I ./googletest/googlemock \
-I ./googletest/googletest/include

```
