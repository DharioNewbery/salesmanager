# 1. Detect all .h files in the mods folder
# wildcard is a built-in make function that finds files
MOD_HEADERS = $(wildcard modules/*.h)

# 2. Convert the list of files into g++ flags
# If MOD_HEADERS is "mods/a.h mods/b.h", 
# this turns it into "-include mods/a.h -include mods/b.h"
INCLUDE_FLAGS = $(foreach header,$(MOD_HEADERS),-include $(header))

# 3. Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# 4. Target: The final executable
TARGET = salesmanager.exe

all: $(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) main.cpp $(INCLUDE_FLAGS) -o $(TARGET)

clean:
	del $(TARGET)