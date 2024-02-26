CC = g++
CFLAGS = -Wall -Wextra -std=c++11
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lenet

SRCDIR = src
HDRDIR = headers
BUILDDIR = build
TARGET = tetris

SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))
DEPS = $(wildcard $(HDRDIR)/*.hpp)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(SFML_LIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(BUILDDIR)/*.o $(TARGET)
