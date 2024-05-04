CXX = g++ 
CXXFLAGS = -std=c++17 -Wall -Wextra -I./include
LFLAGS = -L./files -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SRCDIR = src 
OBJDIR = obj
BINDIR = . 
EXECUTABLE = $(BINDIR)/pvz.out 
MEDIA_PATH = ./files/

SROURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(wildcard $(SRCDIR)/*.hpp)
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I$(MEDIA_PATH)

clean: 
	rm -rf $(OBJDIR)/*.o $(EXECUTABLE) 
