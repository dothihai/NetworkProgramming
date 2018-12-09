all: 	
	gcc main.c -o main `pkg-config --cflags --libs gtk+-3.0`
run: 
	./main
clean: 
	rm main
