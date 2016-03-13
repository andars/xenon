main: main.cc
	g++ $< -o $@ -std=c++11

run: main
	./main > output.ppm
	convert output.ppm output.png
	open output.png

