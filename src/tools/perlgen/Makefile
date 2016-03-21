TARGET = perlgen
LIBS = -lm
CC = clang
CFLAGS = -Wall

default: CFLAGS += -g -DDEBUG
default: $(TARGET)
all: default

release: clean
release: $(TARGET)
release: clean_object_files

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean: clean_emacs
clean: clean_object_files
clean: clean_target
clean: clean_output_files

clean_emacs:
	rm *~ 2>/dev/null ||:

clean_object_files:
	rm -f *.o 2>/dev/null ||:

clean_target:
	rm -f $(TARGET) 2>/dev/null ||:

clean_output_files:
	rm output.txt output.png 2>/dev/null ||:
