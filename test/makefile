include variables.mk
include $(PROJECT_DIR)/variables.mk

HEADER_DIR = $(TEST_HEADER_DIR)
SRC_DIR = $(TEST_SRC_DIR)
OBJ_DIR = $(TEST_OBJ_DIR)

TARGET ?= $(TEST_TARGET)

HEADER_DIRS = $(shell find $(HEADER_DIR) -type d)
HEADER_PATHS = $(addprefix -I ,$(HEADER_DIRS))
PROJECT_HEADER_SUB_DIRS = $(shell find $(PROJECT_DIR)/$(PROJECT_HEADER_DIR) -type d)

PROJECT_HEADER_PATHS = $(addprefix -I ,$(PROJECT_HEADER_DIR))
PROJECT_HEADER_PATHS += $(addprefix -I ,$(PROJECT_HEADER_SUB_DIRS))

PROJECT_OBJ_PATHS = $(shell find $(PROJECT_DIR) -type f -name '*.o')
PROJECT_OBJ_PATHS := $(filter-out %/main.o, $(PROJECT_OBJ_PATHS))

CC = $(TEST_CC)
CFLAGS = $(HEADER_PATHS) $(PROJECT_HEADER_PATHS) $(TEST_CFLAGS)

SRC = $(shell find $(SRC_DIR) -type f -name '*.cpp')
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))
OBJ_SUB_DIRS = $(sort $(dir $(OBJ)))

$(shell mkdir -p $(OBJ_SUB_DIRS))

.PHONY: test
test: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJ) $(PROJECT_OBJ_PATHS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(PROJECT_OBJ_PATHS)

$(OBJ): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp  
	$(CC) $(CFLAGS) -c $< -o $@ 

.PHONY: clean
clean:
	@rm -rf $(OBJ_DIR) vgcore*

.PHONY: purge
purge: clean
	@rm -f $(TARGET)
