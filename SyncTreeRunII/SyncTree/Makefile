CC= g++
CFLAGS=-c -g -Wall -I `root-config --incdir` -I./include
LDFLAGS=`root-config --libs`
SOURCES=$(wildcard ./src/*.cc)
OBJECTS=$(SOURCES:.cc=.o)
EXECUTABLE=generate_syncTree

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cc.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm ./src/*.o ./generate_syncTree  ./src/autoGEN*

dict:
	rootcint -f ./src/autoGENsynctreeLinkDef.cc -c ./include/syncTreeLinkDef.h
