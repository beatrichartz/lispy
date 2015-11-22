TEST_SRC_DIR = tests/src
TEST_OBJ_DIR = tests/obj
TEST_BIN_DIR = bin
TEST_SOURCES = $(wildcard $(TEST_SRC_DIR)/*.c) $(wildcard $(TEST_SRC_DIR)/*/*.c)
TEST_OBJECTS = $(TEST_SOURCES:$(TEST_SRC_DIR)/%.c=$(TEST_OBJ_DIR)/%.o)
TEST_SRC_OBJECTS = $(filter-out $(OBJ_DIR)/$(TARGET).o, $(OBJECTS)) 
TEST_TARGET = test
TEST_CFLAGS = -iquote $(SRC_DIR) -iquote $(TEST_SRC_DIR)

$(TEST_TARGET): $(TEST_BIN_DIR)/$(TEST_TARGET)

$(TEST_BIN_DIR)/$(TEST_TARGET): $(TEST_OBJECTS) $(LIB_OBJECTS) $(OBJECTS)
	$(CC) $(LDFLAGS) $(TEST_SRC_OBJECTS) $(TEST_OBJECTS) -o $@
	$@

$(TEST_OBJECTS): $(TEST_OBJ_DIR)/%.o : $(TEST_SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(TEST_CFLAGS) -c $< -o $@
	@echo "Compiled "$<
