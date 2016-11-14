# Makefile

# Define the compiler to use.
COMPILER = g++

# Define compiler flags.
COMPILER_FLAGS = \
	-D_THREAD_SAFE \
	-Wall \
	-g \
	-std=c++11

# Define directories containing headers to include.
INCLUDE_PATHS = \
	-I../HybridMath/include \
	-I../HybridMath/template \
	-I../HybridStrings/include \
	-I/usr/local/include \
	-I/usr/local/opt/openal-soft/include \
	-I./include

# Define directories containing libraries to include.
LIBRARY_PATHS = \
	-L../HybridMath/lib \
	-L../HybridStrings/lib \
	-L/usr/local/lib

# Define libraries to link into the executable.
LINKER_FLAGS = \
	-lHybridMath \
	-lHybridStrings \
	-framework OpenGL \
	-lGLEW \
	-lSDL2 \
	-lSDL2_image \
	-lSDL2_ttf \
	-ljsoncpp

# Define source files.
SOURCE_FILES = \
	$(wildcard src/*.cpp)

# Define object files.
OBJECT_FILES = \
	$(patsubst src/%.cpp, obj/%.o, $(SOURCE_FILES))

# Define executable file.
EXECUTABLE = bin/hybridgameframework

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECT_FILES)
	$(COMPILER) $(COMPILER_FLAGS) $^ -o $@ $(LIBRARY_PATHS) $(LINKER_FLAGS)

$(OBJECT_FILES): obj/%.o : src/%.cpp
	$(COMPILER) $(COMPILER_FLAGS) -c $< -o $@ $(INCLUDE_PATHS)

clean:
	$(RM) $(EXECUTABLE)
	$(RM) $(wildcard obj/*.o)
