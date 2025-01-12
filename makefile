SRC_FILES = src/main.cpp src/logEntry.cpp
BUILD = build\main.exe

all: clean build

build:
	g++ -g -Ilib/asio $(SRC_FILES) -o $(BUILD) -lws2_32
	
clean:
	del $(BUILD)

open:
	$(BUILD)

debug:
	gdb $(BUILD)

.PHONY: all build clean open debug