CXX := g++
SRCDIR := src
BUILDDIR := build
TARGET := bin/main

CXX_SRCEXT := cpp
CXX_SOURCES := $(shell find $(SRCDIR) -type f -name *.$(CXX_SRCEXT))
OBJECTS += $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(CXX_SOURCES:.$(CXX_SRCEXT)=.o))
CXXFLAGS := -std=c++11
INC := -Iinclude

all: executable

debug: CXXFLAGS += -DDEBUG -g
debug: executable

executable: $(OBJECTS)
	@echo "Linking..."
	@echo "$(CXX) $^ -o $(TARGET) $(LIB)"; $(CXX) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(C_SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo "$(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(CXX_SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo "$(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<"; $(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<

clean:
	@echo "Cleaning...";
	@echo "$(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)
	@echo "$(RM) include/*.gch"; $(RM) include/*.gch
