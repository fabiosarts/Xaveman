# Variables
CC = g++
CFLAGS = -Wall -g
TARGET = Xaveman
LIBS = -lX11 -lXpm

# Default target
all: $(TARGET)

# Linking the final executable
$(TARGET): icons.o Widget.o WButton.o WItemList.o WMainApp.o main.o
	$(CC) $(CFLAGS) icons.o Widget.o WButton.o WItemList.o WMainApp.o main.o $(LIBS) -o $(TARGET)

icons.o: icons.cpp
	$(CC) icons.cpp $(CFLAGS) -c -o icons.o

main.o: main.cpp
	$(CC) main.cpp $(CFLAGS) -c -o main.o

Widget.o: ./widgets/Widget.cpp
	$(CC) ./widgets/Widget.cpp $(CFLAGS) -c -o Widget.o

WButton.o: Widget.o ./widgets/WButton.cpp
	$(CC) ./widgets/WButton.cpp $(CFLAGS) -c -o WButton.o

WItemList.o: Widget.o ./widgets/WItemList.cpp
	$(CC) ./widgets/WItemList.cpp $(CFLAGS) -c -o WItemList.o

WMainApp.o: Widget.o ./widgets/WMainApp.cpp
	$(CC) ./widgets/WMainApp.cpp $(CFLAGS) -c -o WMainApp.o

# Clean up build files
clean:
	rm -f *.o $(TARGET)

# Phony targets
.PHONY: all clean
