# Google Test

## 구글 테스트 프레임워크 환경 설정

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

# gmock_main.cc
$ g++ -c -std=c++14 -O2 ./googletest/googlemock/src/gmock_main.cc \
-I ./googletest/googletest/include \
-I ./googletest/googlemock/include

# libgtest.a
$ ar rcv libgtest.a gmock-all.o gtest-all.o gmock_main.o


```
