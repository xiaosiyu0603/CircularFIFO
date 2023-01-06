

filelist_c   = main.c circular_fifo.c
headlist_c   = circular_fifo.h
filelist_cpp = main.cpp
headlist_cpp = circular_fifo

main_c.exe: $(filelist_c) $(headlist_c)
	gcc -std=c99 $(filelist_c) -o $@

main_cpp.exe: $(filelist_cpp) $(headlist_cpp)
	g++ -std=c++11 $(filelist_cpp) -o $@

.PHONY: c
c: main_c.exe
	$<

.PHONY: cpp
cpp: main_cpp.exe
	$<

