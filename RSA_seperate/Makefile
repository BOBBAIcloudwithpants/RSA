CC := g++
FLAGS := -std=c++11 -w
INC_DIR := include
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
TEST_DIR := test
INCLUDE := -I./$(INC_DIR)

$(BIN_DIR)/main: $(BUILD_DIR)/Node.o $(BUILD_DIR)/Int.o $(BUILD_DIR)/OctetString.o $(BUILD_DIR)/Encryption.o $(BUILD_DIR)/main.o
	@mkdir -p $(BIN_DIR)
	$(CC) $(FLAGS) $(INCLUDE) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) $(INCLUDE) -c -o $@ $<

.PHONY: clean

testing: $(BUILD_DIR)/int_test.o $(BUILD_DIR)/encryption_test.o $(BUILD_DIR)/test.o
	$(CC) $(FLAGS) $(INCLUDE) $^ -o $@
	./testing
	@rm -rf testing

# $(BUILD_DIR)/test.o: $(TEST_DIR)/test.c $(TEST_DIR)/int_test.c $(TEST_DIR)/encryption_test.c
# 	@mkdir -p $(BUILD_DIR)
# 	$(CC) $(FLAGS) $(INCLUDE) -c -o $@ $<

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c  $(TEST_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) $(INCLUDE) -c -o $@ $^

# $(BUILD_DIR)/encryption_test.o: $(SRC_DIR)/Encryption.c  $(TEST_DIR)/encryption_test.c
# 	@mkdir -p $(BUILD_DIR)
# 	$(CC) $(FLAGS) $(INCLUDE) -c -o $@ $


clean:
	@rm -rf $(BUILD_DIR)
	@rm -rf $(BIN_DIR)