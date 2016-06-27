CXX_FLAGS = -std=c++11 -Weverything \
			-Wno-missing-prototypes -Wno-pedantic \
			-Wno-padded -Wno-weak-vtables -Wno-vla \
			-O3

SOURCES = $(wildcard *.cc)
HEADERS = $(wildcard *.h)

main: $(SOURCES) $(HEADERS)
	clang++ $(SOURCES) -o $@ $(CXX_FLAGS)

debug: CXX_FLAGS += -g
debug: main

run: main
	time ./main > output.ppm
	convert output.ppm output.png
	open output.png

clean:
	rm -f main

