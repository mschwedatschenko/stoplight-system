objects = main.c
CFLAGS = -g
TARGET = main

$(TARGET): $(objects)
        gcc $(CFLAGS) -o $(TARGET) $(objects)

clean:
        rm $(TARGET)