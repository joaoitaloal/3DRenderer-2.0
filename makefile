ifeq ($(OS), Windows_NT)
    EXE = .exe
else
    EXE =
endif

CC = g++
CFLAGS = -Wall -lm

INCLUDES = \
    -I ./dependencies/include

LDFLAGS = \
    -L ./dependencies/lib

LDLIBS = -lraylib -lgdi32 -lwinmm

BUILD_DIR = build
TARGET ?= $(BUILD_DIR)/main$(EXE)
SRC ?= ./src/main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC) -o $(TARGET) $(LDFLAGS) $(LDLIBS)

clean:
ifeq ($(OS), Windows_NT)
	del /Q $(BUILD_DIR)
else # não sei como o rm se comporta, talvez tenha que ser diferente esse comando
	rm $(TARGET) 
endif

run:
	$(TARGET)

test:
	echo $(OS)
