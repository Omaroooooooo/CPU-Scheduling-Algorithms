CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iheader

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

TARGET = scheduler

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET)
