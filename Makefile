CXX      = g++
CXXFLAGS = -Wall -Wextra -std=c++17

TARGET   = Audio_App

SRCS     = main.cpp ongaku.cpp
OBJS     = $(SRCS:.cpp=.o)

LIBS     = -lsfml-system -lsfml-audio -lrtaudio -lpthread

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean