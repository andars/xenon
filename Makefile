BUILD_DIR = ./build
SRC_DIR = .

CXXFLAGS = -std=c++11 -Weverything \
			-Wno-missing-prototypes -Wno-pedantic \
			-Wno-padded -Wno-weak-vtables -Wno-vla \
			-O3

SOURCES = $(wildcard *.cc)
OBJECTS = $(SOURCES:%=$(BUILD_DIR)/%.o)
HEADERS = $(wildcard *.h)

main: $(OBJECTS) $(HEADERS)
	$(CXX) $(OBJECTS) -o $@ $(CXXFLAGS)

$(BUILD_DIR)/%.cc.o: %.cc
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@



debug: CXX_FLAGS += -g
debug: main

run: main
	time ./main > output.ppm
	convert output.ppm output.png
	open output.png

clean:
	rm -f main
	rm -rf $(BUILD_DIR)

