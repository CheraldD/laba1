.PHONY: all clean

CXX = g++


CXXFLAGS = -Wall 


TARGET = modAlphaCipher


SOURCES = main.cpp modAlphaCipher.cpp


OBJECTS = $(SOURCES:.cpp=.o)


DEPS = modAlphaCipher.h


all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(CXXFLAGS) -o $(TARGET) 

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
