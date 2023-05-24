# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -std=c99

# Executable name
EXEC = tex_cleanup

# Source files
SOURCES = tex_cleanup.c

# Object files
OBJS = $(SOURCES:.c=.o)

# Build rules
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $<

# Clean rules
.PHONY: clean

clean:
	rm -f $(OBJS) $(EXEC)
