CC = g++
CFLAGS = -W -O2
LINK = -lGLU -lGL -lglut 
SRC_DIR = ./src
BIN_DIR = ./bin
INCLUDES = ./include

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(addprefix $(BIN_DIR)/, $(notdir $(SOURCES:.cpp=.o)))

EXECUTABLE = $(BIN_DIR)/BoxGame

all: $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(CFLAGS) $(BIN_DIR)/*.o -o $@ $(LINK)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@
	
clean:
	rm -rf $(BIN_DIR)/*

