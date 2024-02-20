# Compiler
CC := g++
# Flags
CFLAGS := -Wall -Wextra -std=c++11
SFMLFLAGS := -lsfml-graphics -lsfml-window -lsfml-system
# Directories
SRCDIR := src
INCDIR := headers
BUILDDIR := build
TARGET := executable

# Files to compile
CPPFILES := $(wildcard $(SRCDIR)/*.cpp)
HPPFILES := $(wildcard $(INCDIR)/*.hpp)
OBJECTS := $(CPPFILES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

# Make all
all: $(TARGET)

# Target
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(SFMLFLAGS)

# Compile .cpp files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(HPPFILES)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

# Clean
clean:
	rm -f $(BUILDDIR)/*.o $(TARGET)
