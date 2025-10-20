CXX = g++
CXXFLAGS = -std=c++11
LDFLAGS = -lopengl32 -lglu32 -lfreeglut -lwinmm

SRCDIR = src
OBJDIR = obj

SOURCES = $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR)/core/*.cpp) $(wildcard $(SRCDIR)/entities/*.cpp) $(wildcard $(SRCDIR)/ui/*.cpp) $(wildcard $(SRCDIR)/utils/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

EXECUTABLE = pacman.exe

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	./$(EXECUTABLE)

clean:
	rm -rf $(OBJDIR) $(EXECUTABLE)
