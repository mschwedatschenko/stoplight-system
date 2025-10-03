objects = main.c
CFLAGS = -g

main:
	gcc $(CFLAGS) -o main $(objects)

clean:
	rm main $(objects)