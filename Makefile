CXX_FLAGS = -std=c++11 -Weverything \
			-Wno-missing-prototypes -Wno-pedantic \
			-Wno-padded -Wno-weak-vtables \
			-O3

SOURCES = $(wildcard *.cc)
HEADERS = $(wildcard *.h)

main: $(SOURCES) $(HEADERS)
	g++ $(SOURCES) -o $@ -std=c++11 $(CXX_FLAGS)

run: main
	./main > output.ppm
	convert output.ppm output.png
	open output.png

clean:
	rm -f main

