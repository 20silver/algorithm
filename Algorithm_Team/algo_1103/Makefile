CC = g++
CFLAGS = -std=c++11 -lncurses
TARGET = pushbox

$(TARGET) : pushbox.cpp Level.cpp Node.cpp Point.cpp State.cpp
	$(CC) -o $(TARGET) pushbox.cpp Level.cpp Node.cpp Point.cpp State.cpp $(CFLAGS)

clean :
	rm pushbox
