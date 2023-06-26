include variables.mk

HEADER_DIR = $(PROJECT_HEADER_DIR)
SRC_DIR = $(PROJECT_SRC_DIR)
OBJ_DIR = $(PROJECT_OBJ_DIR)

TEST_DIR = $(PROJECT_TEST_DIR)
TARGET = $(PROJECT_TARGET)
  
HEADER_SUB_DIRS = $(shell find $(HEADER_DIR) -type d)

HEADER_PATHS = $(addprefix -I ,$(HEADER_DIR))
HEADER_PATHS += $(addprefix -I ,$(HEADER_SUB_DIRS))

CLI_FLAGS = 
CC = $(PROJECT_CC)
CFLAGS = $(HEADER_PATHS) $(PROJECT_CFLAGS) $(CLI_FLAGS)

SRC = $(shell find $(SRC_DIR) -type f -name '*.cpp')
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))
OBJ_SUB_DIRS = $(sort $(dir $(OBJ)))

$(shell mkdir -p $(OBJ_SUB_DIRS))

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(OBJ_PATHS)

$(OBJ): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: run
run: $(TARGET)
	./$(TARGET)

.PHONY: clean
clean:
	@rm -rf $(OBJ_DIR) vgcore* 
	@$(MAKE) --no-print-directory -C $(TEST_DIR) clean

.PHONY: purge 
purge: clean
	@rm -f $(TARGET)
	@$(MAKE) --no-print-directory -C $(TEST_DIR) purge

.PHONY: test
test: $(TARGET)
	$(MAKE) --no-print-directory -C $(TEST_DIR)

