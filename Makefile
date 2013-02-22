BUILD	 = $(PrjHome)/build
EXECS	 = $(BUILD)/bin
OBJS	 = $(BUILD)/obj
SLIB	 = $(BUILD)/lib

TAGPARSERSRC = $(PrjHome)/tagparser

TAGPARSER	 = $(BUILD)/bin/tagparser.exe

CC	 = g++
CFLAGS   = -Wall -DDEBUG
#CFLAGS   = -Wall
AR	 = ar

OBJECTS := $(patsubst $(TAGPARSERSRC)/%.cpp, $(OBJS)/%.o, $(wildcard $(TAGPARSERSRC)/*.cpp))

all: $(TAGPARSER)

.PHONY: clean

$(TAGPARSER) : $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

$(OBJS)/%.o : $(TAGPARSERSRC)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean :	
	-rm $(TAGPARSER) $(OBJECTS)
