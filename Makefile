CC = g++
CFLAGS = -std=c++11

app: src/app.cpp
	$(CC) $(CFLAGS) -o app src/app.cpp

test: src/test.cpp
	$(CC) $(CFLAGS) -o test src/test.cpp

clean:
	rm -rf *.o src/*.o app test
