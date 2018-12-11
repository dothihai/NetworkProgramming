all: 	
	gcc main.c -o main -g `pkg-config --cflags --libs gtk+-3.0`
w: 	
	gcc main.c -o main -w -g `pkg-config --cflags --libs gtk+-3.0`	
run: w
	./main
clean: 
	rm main
s:	
	gcc echoServer.c -o server -g && ./server
test:
	gcc test.c -o test -g `pkg-config --cflags --libs gtk+-3.0`