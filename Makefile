# Compiler
CC = gcc

# Compiler flags
CFLAGS = -I./src/include -Wall

# Source files
SRCS = \
		src/read_stream.c \
		src/utils/utils.c \
		test/read_stream.c

# Object files
OBJS = $(SRCS:.c=.o)

# Output executable
TARGET = read_stream_test

# Default rule to compile the program
all: $(TARGET)

# Rule to link object files and create the executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Rule to compile individual .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and the executable
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
