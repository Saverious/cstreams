# Compiler
CC = gcc

# Compiler flags
CFLAGS = -I./src/include -Wall

# Source files
SRCS = \
		src/read_stream.c \
		test/rstream1.c \
		test/rstream2.c

# Object files
OBJS = $(SRCS:.c=.o)

# Output executable
TARGET = rstream

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
