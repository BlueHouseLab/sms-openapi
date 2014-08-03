CFLAGS=-Wall -O2
all: sendsms result

sendsms: sendsms.o
	$(CC) -o $@ $< `pkg-config --libs libcurl`

sendsms.o: sendsms.c conf.h
	$(CC) $(CFLAGS) -o $@ -c $< `pkg-config --cflags libcurl`

result: result.o
	$(CC) -o $@ $< `pkg-config --libs libcurl`

result.o: result.c conf.h
	$(CC) $(CFLAGS) -o $@ -c $< `pkg-config --cflags libcurl`

clean:
	rm -f *.o sendsms result
