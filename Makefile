CC=gcc -std=c11
CFLAGS=-c -g

bin=decode

obj=decode.o


decode: $(obj)
	$(CC) -o $(bin) $(obj)

decode.o: decode.c
	$(CC) $(CFLAGS) decode.c 

clean:
	rm -f $(obj)
