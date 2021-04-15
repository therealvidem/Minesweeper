# Taken from https://www.reddit.com/r/raylib/comments/ecz6ja/problem_getting_started_with_project_cmake_file/fbf7e3o/

BUILD = build
TARGET = $(BUILD)/Minesweeper

SRC = src/main.c

INCLUDE = -I include/
LIBS = -L lib/
LIBS += -lraylib -lopengl32 -lgdi32 -lwinmm -lpthread

CXX = gcc
FLAGS = -Wall

OBJ = $(patsubst %.c, %.o, $(SRC))
DEPS = $(wildcard *.h)

%.o : %.c $(DEPS)
	$(CXX) $(INCLUDE) $(FLAGS) -c $< -o $(BUILD)/$(@F) $(LIBS)

all: $(TARGET)

debug: FLAGS += -DDEBUG -g
debug: $(TARGET)

$(TARGET) : $(OBJ)
	$(CXX) $(INCLUDE) $(FLAGS) $(BUILD)/$(^F) -o $@ $(LIBS)

clean:
	rm -f $(TARGET)

run:
	@./$(TARGET)

# gcc -g src/main.c -o build/Minesweeper.exe -std=c99 -L include/ -Wall -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -lpthread