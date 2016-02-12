TARGET = a.out
LIBS = -lglfw -lGL
CC = clang
CFLAGS = -Wall

default: CFLAGS += -g -DDEBUG
default: $(TARGET)
all: default

release: $(TARGET)

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	-rm *~
	-rm -f *.o
	-rm -f $(TARGET)
