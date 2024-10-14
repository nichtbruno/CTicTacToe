CC := gcc

SRC := $(shell find . -name '*.c')
HEADERS := $(shell find . -name '*.h')
OBJ := $(SRC:.c=.o)

TARGET := main

CFLAGS := -std=c17 -Wall -lm

all: $(TARGET)
	@echo "Build complete 😎"

-include $(OBJ:.o=.d)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(TARGET)

%.d: %.c
	$(CC) $(CFLAGS) -MM -MT $(@:.d=.o) $< > $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET) $(OBJ:.o=.d)

run:
	./$(TARGET)

.PHONY: all clean
