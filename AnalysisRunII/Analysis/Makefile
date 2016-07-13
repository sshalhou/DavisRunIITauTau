CC= g++

CFLAGS= -std=c++11 -c -g -Wall -MMD -MP -I `root-config --incdir` 

CFLAGS += -I./include
CFLAGS += -I./HTT-utilities/LepEffInterface/interface
CFLAGS += -I./

LDFLAGS=`root-config --libs`
SOURCES=$(wildcard ./src/*.cc)
SOURCES += $(wildcard ./operations/*.cc)
SOURCES += $(wildcard ./HTT-utilities/LepEffInterface/LepEffInterface/src/*.cc)
OBJECTS=$(SOURCES:.cc=.o)
EXECUTABLE=run_analysis
DEPS = $(SOURCES:.cc=.d)


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cc.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm ./src/*.o ./run_analysis  ./src/autoGEN* ./src/*.d

dictOSX:
	rootcint -f ./src/autoGENsynctreeLinkDef.cc -c ./include/syncTreeLinkDef.h

-include $(DEPS)
