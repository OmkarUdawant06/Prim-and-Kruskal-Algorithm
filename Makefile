CC=g++
TARGET=project4
all:
	$(CC) UDAWANT_OMKAR_pa4.cpp -o $(TARGET)
clean:
	rm -f *.o *.d *~ $(TARGET)