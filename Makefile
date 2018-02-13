TARGET=maze
SRC_DIR?=src
BUILD_DIR?=build

C_SRC= \
$(SRC_DIR)/bitmap.c \
$(SRC_DIR)/dynamic_array.c \
$(SRC_DIR)/model.c \
$(SRC_DIR)/prims_maze.c \
$(SRC_DIR)/renderer.c \
$(SRC_DIR)/maze.c

CFLAGS+=-Wall -Werror
CFLAGS+=-std=c99
CFLAGS+=-O0
CFLAGS+=-g3
CFLAGS+=-MD -MP

RM=rm -f --

C_OBJS=$(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(C_SRC))
OBJS=$(C_OBJS)


all: $(BUILD_DIR)/$(TARGET)


$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH) $^ $(LOADLIBES) $(LDLIBS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c -o $@ $<


clean:
	$(RM) $(BUILD_DIR)/$(TARGET)
	$(RM) $(OBJS)
	$(RM) $(OBJS:.o=.d)

.PHONY: all clean
-include $(C_SRC:.c=.d)
