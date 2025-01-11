SRC_FILES = src/main.cpp src/logEntry.cpp
BUILD = build\main.exe

all:
	g++ -Ilib/asio $(SRC_FILES) -o $(BUILD) -lws2_32
	
clean:
	del $(BUILD)

open:
	$(BUILD)