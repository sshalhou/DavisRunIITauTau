CC= g++

CFLAGS= -std=c++11 -c -g -Wall -MMD -MP -I `root-config --incdir` 

CFLAGS += -I./include
CFLAGS += -I./HTT-utilities/LepEffInterface/interface
CFLAGS += -I./HTT-utilities/QCDModelingEMu/interface
CFLAGS += -I./

LDFLAGS=`root-config --libs`
SOURCES=$(wildcard ./src/*.cc)
SOURCES += $(wildcard ./HTT-utilities/QCDModelingEMu/src/*.cc)
SOURCES += $(wildcard ./HTT-utilities/LepEffInterface/src/*.cc)
SOURCES += $(wildcard ./operations/*.cc)
OBJECTS=$(SOURCES:.cc=.o)
EXECUTABLE=run_analysis
DEPS = $(SOURCES:.cc=.d)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cc.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm ./src/*.o ./run_analysis  ./src/autoGEN* ./src/*.d ./HTT-utilities/LepEffInterface/src/*o ./HTT-utilities/QCDModelingEMu/src/*o

dictOSX:
	rootcint -f ./src/autoGENsynctreeLinkDef.cc -c ./include/syncTreeLinkDef.h

-include $(DEPS)
