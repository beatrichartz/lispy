clean:
	rm -f $(LIB_OBJECTS)
	rm -f $(OBJECTS)
	rm -f $(TEST_OBJECTS)
	rm -f $(TEST_RUNNER_OBJECTS)
	rm -f $(BIN_DIR)/$(TARGET)
	rm -f $(TEST_BIN_DIR)/$(TEST_TARGET)
	rm -f $(TEST_BIN_DIR)/$(TEST_TARGET)_debug
	@echo "Cleaned $(TARGET)"

clean_$(TARGET):
	rm -f $(OBJECTS)
	rm -f $(BIN_DIR)/$(TARGET)

clean_$(TEST_TARGET):
	rm -f $(TEST_OBJECTS)
	rm -f $(TEST_BIN_DIR)/$(TEST_TARGET)
	rm -f $(TEST_BIN_DIR)/$(TEST_TARGET)_debug
	@echo "Cleaned $(TEST_TARGET)"

clean_test_runner:
	rm -f $(TEST_RUNNER_OBJECTS)
	@echo "Cleaned test runner"
