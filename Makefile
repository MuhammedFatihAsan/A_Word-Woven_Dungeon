CC = gcc
CFLAGS = -Wall -Wextra -g -I./src/include -D'GAME_DATA_PATH="$(CURDIR)/game_data/"'
SRC_DIR = ./src
OBJ_DIR = ./obj
BIN_DIR = .
ifdef ComSpec
    BIN = $(BIN_DIR)/A_Word-Woven_Dungeon.exe  # for Windows için .exe
else
    BIN = $(BIN_DIR)/A_Word-Woven_Dungeon      # for Linux/macOS
endif

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) -o $@ $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN)

run: $(BIN)
	./$(BIN)