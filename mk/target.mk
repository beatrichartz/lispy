SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

TARGET = lispy

$(TARGET): $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(LIB_OBJECTS) $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(OBJECTS): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<

