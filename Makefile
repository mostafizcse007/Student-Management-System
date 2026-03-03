CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = student_management

all: $(TARGET)

$(TARGET): LabProject.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) LabProject.cpp

clean:
	rm -f $(TARGET)

.PHONY: all clean
