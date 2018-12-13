TARGET   = sts 
CC	   = g++
CFLAGS   = -std=c++14 -Wall

LINKER   = g++
LFLAGS   = -std=c++14 -Wall

SRCDIR   = src
INCDIR   = include
OBJDIR   = obj
BINDIR   = bin

SOURCES  := $(wildcard $(SRCDIR)/*.cc)
INCLUDES := -I./include
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cc=$(OBJDIR)/%.o)
rm	   = rm -f


$(BINDIR)/$(TARGET): $(OBJECTS)
	$(LINKER) $(OBJECTS) $(LFLAGS) -o $@

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cc
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

.PHONY: clean
clean:
	$(rm) $(OBJECTS)

.PHONY: remove
remove: clean
	$(rm) $(BINDIR)/$(TARGET)
