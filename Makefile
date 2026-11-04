
# ==========================================
# Configuration
# ==========================================

CC       := gcc
TARGET   := mc

STD      := c11
OPT      := 2

CFLAGS   := -std=$(STD) -O$(OPT) -Wall -Wextra -Wpedantic
CPPFLAGS := -Iinclude -MMD -MP
LDFLAGS  :=
LDLIBS   :=

BUILD    := build

# ==========================================
# Source files
# ==========================================

SOURCES := $(wildcard *.c)

OBJECTS := $(patsubst %.c,$(BUILD)/%.o,$(SOURCES))
DEPS    := $(OBJECTS:.o=.d)

# ==========================================
# Build rules
# ==========================================

.PHONY: all clean rebuild

all: $(TARGET)

# Link executable
$(TARGET): $(OBJECTS)
	@echo "  LINK    $@"
	@$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

# Compile individual source files
$(BUILD)/%.o: %.c | $(BUILD)
	@echo "  CC      $<"
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Create build directory
$(BUILD):
	@mkdir -p $@

# ==========================================
# Utilities
# ==========================================

clean:
	@echo "  CLEAN"
	@rm -rf $(BUILD) $(TARGET)

rebuild: clean all

# ==========================================
# Header dependencies
# ==========================================

-include $(DEPS)