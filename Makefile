CXX_FLAGS = -std=c++11 -Weverything -Wno-missing-prototypes 

SOURCES = $(wildcard *.cc) $(wildcard *.h)

main: $(SOURCES) 
	g++ $< -o $@ -std=c++11 $(CXX_FLAGS)

run: main
	./main > output.ppm
	convert output.ppm output.png
	open output.png

clean:
	rm -f main

