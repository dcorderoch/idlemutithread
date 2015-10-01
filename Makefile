OBJECTS := *.o
SOURCES := *.c
HEADERS := *.h

CC := gcc
CFLAGS := -O2 -Wall -g -pthread
NAME := threads

all : $(NAME)

$(NAME) : $(OBJECTS)
	$(CC) $(OBJECTS) -o $(NAME) $(CFLAGS)
%.o : %.c
	$(CC) $(SOURCES) -c $(CFLAGS)

.PHONY : clean
clean:
	rm -f $(OBJECTS) $(NAME)
.PHONY : run
run : all
	./$(NAME)
