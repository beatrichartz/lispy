include mk/config.mk
include mk/target.mk
include mk/tests.mk

all: $(SOURCES) $(TARGET) $(TEST_SOURCES) $(TEST_TARGET)
clean:
	rm -f $(BIN_DIR)/$(TARGET)
	rm -f $(TEST_BIN_DIR)/$(TEST_TARGET)

include mk/libs.mk
