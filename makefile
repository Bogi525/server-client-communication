SERVER_FILES = src/server.cpp src/main_server.cpp src/logEntry.cpp src/user.cpp src/users.cpp
CLIENT_FILES = src/client.cpp src/main_client.cpp src/logEntry.cpp
BUILD_SERVER = build\server.exe
BUILD_CLIENT = build\client.exe

all: clean build_server build_client

build_server:
	g++ -g -Ilib/asio $(SERVER_FILES) -o $(BUILD_SERVER) -lws2_32

build_client:
	g++ -g -Ilib/asio $(CLIENT_FILES) -o $(BUILD_CLIENT) -lws2_32
	
clean:
	del $(BUILD_SERVER) $(BUILD_CLIENT)

open_server:
	$(BUILD_SERVER)

open_client:
	$(BUILD_CLIENT)

debug_server:
	gdb $(BUILD_SERVER)

debug_client:
	gdb $(BUILD_CLIENT)

.PHONY: all build clean open debug