all:
	diff --color -u main.cpp <(clang-format -style="{BasedOnStyle: google, ColumnLimit: 0}" main.cpp)
	clang++ -D DEBUG -std=c++17 -O2 -o main main.cpp
