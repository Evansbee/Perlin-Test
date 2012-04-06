CC=clang
CFLAGS=-c -O2 -Wall 
LDFLAGS=-lm
SOURCES=main.c PerlinNoise.c 
OBJECTS=$(SOURCES:.c=.o)
OUTFILE=perlin

all: $(SOURCES) $(OUTFILE)
	
$(OUTFILE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *o $(OUTFILE)
