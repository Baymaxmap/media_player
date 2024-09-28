CC = g++
CFLAGS = -g -c -Wall -I$(INC_H) -I/usr/include/SDL2
LDFLAGS = -ltag -lSDL2 -lSDL2_mixer
SRC_C = src
INC_H = inc
BUILD_DIR = build
TARGET = $(BUILD_DIR)/prog

C_SRC = $(wildcard $(SRC_C)/*.cpp)
OBJS = $(patsubst $(SRC_C)/%.cpp, $(BUILD_DIR)/%.o, $(C_SRC))

all: $(BUILD_DIR) $(TARGET)
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o : $(SRC_C)/%.cpp
	$(CC) $(CFLAGS) $< -o $@

$(TARGET): $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@

clean:
	rm $(BUILD_DIR)/*.o $(BUILD_DIR)/prog

run:
	$(TARGET)