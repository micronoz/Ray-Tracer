CC = g++ -no-pie
ifeq ($(shell sw_vers 2>/dev/null | grep Mac | awk '{ print $$2}'),Mac)
CFLAGS = -g -DGL_GLEXT_PROTOTYPES -DGL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED -DOSX -Wno-deprecated-register -Wno-deprecated-declarations -Wno-shift-op-parentheses
INCFLAGS = -I./glm-0.9.7.1 -I/usr/X11/include -I./include/
LDFLAGS = -framework GLUT -framework OpenGL -L./lib/mac/ \
		-L"/System/Library/Frameworks/OpenGL.framework/Libraries" \
		-lGL -lGLU -lm -lstdc++ -lfreeimage
else
CFLAGS = -g -DGL_GLEXT_PROTOTYPES 
INCFLAGS = -I./glm-0.9.7.1 -I./include/ -I/usr/X11R6/include -I/sw/include \
		-I/usr/sww/include -I/usr/sww/pkg/Mesa/include
LDFLAGS = -L/usr/X11R6/lib -L/sw/lib -L/usr/sww/lib -L./lib/nix/ \
		-L/usr/sww/bin -L/usr/sww/pkg/Mesa/lib -lglut -lGL -lX11 -lfreeimage
endif

RM = /bin/rm -f 
all: transforms
transforms: main.o Transform.o readfile.o Scene.o
	$(CC) $(CFLAGS) -o raytracer main.o Transform.o readfile.o Scene.o $(INCFLAGS) $(LDFLAGS) 
main.o: main.cpp Transform.h variables.h Shape.h Triangle.h Sphere.h Raytracer.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c main.cpp
readfile.o: readfile.cpp Triangle.h Sphere.h readfile.h variables.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c readfile.cpp
Transform.o: Transform.cpp Transform.h 
	$(CC) $(CFLAGS) $(INCFLAGS) -c Transform.cpp
Scene.o: Scene.cpp Scene.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Scene.cpp
#Triangle.o: Triangle.cpp Triangle.h Shape.h
#	$(CC) $(CFLAGS) $(INCFLAGS) -c Triangle.cpp
clean: 
	$(RM) *.o transforms *.png


 
