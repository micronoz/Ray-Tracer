CC = g++
CFLAGS = -O3 -funroll-loops -g
#CFLAGS = 
INCFLAGS = -I./glm-0.9.7.1 -fopenmp
LDFLAGS = -lfreeimage

RM = /bin/rm -f 
all: raytracer
raytracer: main.o readfile.o
	$(CC) $(CFLAGS) -o raytracer main.o readfile.o $(INCFLAGS) $(LDFLAGS) 
main.o: main.cpp readfile.o Raytracer.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c main.cpp
readfile.o: readfile.cpp Shape.h Triangle.h Sphere.h Light.h readfile.h variables.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c readfile.cpp
#Transform.o: Transform.cpp Transform.h 
#	$(CC) $(CFLAGS) $(INCFLAGS) -c Transform.cpp
clean: 
	$(RM) *.o *.png raytracer hw3.zip
zip:
	zip hw3.zip *.png
test: clean all
	./raytracer sample-scenes/scene4-emission.test
	./raytracer sample-scenes/scene4-specular.test
	./raytracer sample-scenes/scene4-diffuse.test
	./raytracer sample-scenes/scene4-ambient.test
	./raytracer sample-scenes/scene5.test
	./raytracer sample-scenes/scene6.test
	./raytracer sample-scenes/scene7.test
sub: test zip
final: sub
	zip Ozberkman_Nabi_HW4_Full.zip *



 
