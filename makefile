# Compiler
CC = gcc

# Directories
INCLUDE_DIR = include

# Flags
CFLAGS = -I$(INCLUDE_DIR) -Wall

# Source Files
SRC_FILES = main.c movement.c ai.c game_objects.c game_render.c menu.c utility.c

# Output binary
TARGET = snake_game

# Build rules
all: $(TARGET)

$(TARGET): $(SRC_FILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC_FILES)

clean:
	del $(TARGET)

# For debugging
debug: CFLAGS += -g
debug: $(TARGET)
