main: main.cpp roundrobin.cpp
    clang++ -std=c++11 main.cpp roundrobin.cpp

clean:
    rm main;