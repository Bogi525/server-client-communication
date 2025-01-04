SRC_FILES = src/main.cpp src/logEntry.cpp
BUILD = build\main.exe

all:
	g++ $(SRC_FILES) -o $(BUILD)
clean:
	del $(BUILD)