GPP = g++
GPPFLAGS = -std=c++2a -Wall -Wextra -I./include
LFLAGS = -L/files -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SRC_DIR = src
OBJ_DIR = obj
EXES = ./pvz.out
MEDIA_PATH = ./files/

SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))
 
clean:  all
	rm -rf $(OBJ_DIR)/*.o

all : $(EXES)

$(EXES) : $(OBJECTS)
	$(GPP) $(GPPFLAGS) -o $@ $^ $(LFLAGS)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp $(wildcard $(SRC_DIR)/*.h)
	mkdir -p $(OBJ_DIR)
	$(GPP) $(GPPFLAGS) -c $< -o $@ -I$(MEDIA_PATH)
