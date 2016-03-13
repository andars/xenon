CXX_FLAGS = -std=c++11 -Weverything -Wno-missing-prototypes 

main: main.cc
	g++ $< -o $@ -std=c++11 $(CXX_FLAGS)

run: main
	./main > output.ppm
	convert output.ppm output.png
	open output.png

clean:
	rm -f main

