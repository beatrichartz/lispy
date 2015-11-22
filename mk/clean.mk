clean:
	rm -f $(LIB_OBJECTS)
	rm -f $(OBJECTS)
	rm -f $(TEST_OBJECTS)
	rm -f $(BIN_DIR)/$(TARGET)
	rm -f $(TEST_BIN_DIR)/$(TEST_TARGET)
	@echo "Cleaned $(TARGET)"
