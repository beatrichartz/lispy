LIB_SRC_DIR = libs
LIB_OBJ_DIR = obj
LIB_SOURCES = $(wildcard $(LIB_SRC_DIR)/*.c)
LIB_OBJECTS = $(LIB_SOURCES:$(LIB_SRC_DIR)/%.c=$(LIB_OBJ_DIR)/%.o)

$(LIB_OBJECTS): $(LIB_OBJ_DIR)/%.o : $(LIB_SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<

