CXX = g++
CXXFLAGS = -std=c++20 -Wall

INCLUDES = -I/opt/homebrew/Cellar/sfml/2.6.1/include -I./View -I./Model -I./Controller
LIBDIRS = -L/opt/homebrew/Cellar/sfml/2.6.1/lib
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

SRCS = $(shell find . -name '*.cpp')
OBJS = $(SRCS:.cpp=.o)

EXEC = main

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBDIRS) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

.PHONY: all clean

