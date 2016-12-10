CC = g++ # This is the main compiler
SRCDIR = src
BUILDDIR = build
TARGET = bin/game
 
SRCEXT = cpp
SOURCES_TEST = $(shell find test -type f -name *.$(SRCEXT))
SOURCES = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS = -g --std=c++11 -DTIXML_USE_STL -DDEBUG
LIB = -L/Users/linorabolini/Documents/Projects/Cpp/SFML/SFML-2.4.1/lib -lsfml-graphics -lsfml-window -lsfml-system
INC = -I include -I /Users/linorabolini/Documents/Projects/Cpp/SFML/SFML-2.4.1/include

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(shell dirname $@)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

# Game
game: $(TARGET)

# Tests
tests: $(SOURCES_TEST)
	$(CC) $(CFLAGS) $^ $(INC) $(LIB) -o bin/tests

test/%.o: tests/%.cpp
	@mkdir -p $(shell dirname $@)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

.PHONY: clean