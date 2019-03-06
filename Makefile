CC = g++
CFLAGS = -Ofast -funroll-loops
INCFLAGS = -I./glm-0.9.7.1
LDFLAGS = -lfreeimage

RM = /bin/rm -f 
all: raytracer
raytracer: main.o Transform.o readfile.o
	$(CC) $(CFLAGS) -o raytracer main.o Transform.o readfile.o $(INCFLAGS) $(LDFLAGS) 
main.o: main.cpp readfile.o Raytracer.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c main.cpp
readfile.o: readfile.cpp Shape.h Triangle.h Sphere.h readfile.h variables.h Transform.o
	$(CC) $(CFLAGS) $(INCFLAGS) -c readfile.cpp
Transform.o: Transform.cpp Transform.h 
	$(CC) $(CFLAGS) $(INCFLAGS) -c Transform.cpp
clean: 
	$(RM) *.o *.png raytracer


 
