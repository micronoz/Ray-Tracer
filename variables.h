/*****************************************************************************/
/* This is the program skeleton for homework 2 in CSE167 by Ravi Ramamoorthi */
/* Extends HW 1 to deal with shading, more transforms and multiple objects   */
/*****************************************************************************/

// This is the basic include file for the global variables in the program.
// Since all files need access to it, we define EXTERN as either blank or
// extern, depending on if included in the main program or not.

#ifdef MAINPROGRAM
#define EXTERN
#else
#define EXTERN extern
#endif


EXTERN vec3 eyeinit;
EXTERN vec3 upinit;
EXTERN vec3 center;

EXTERN int screenwidth, screenheight;
EXTERN float fovy;


// Materials (read from file)
// With multiple objects, these are colors for each.
EXTERN float ambient[3];
EXTERN float diffuse[3];
EXTERN float specular[3];
EXTERN float emission[3];
EXTERN float shininess;

//Define vertices
EXTERN int maxverts;
EXTERN vector<vec4> vertices;
EXTERN vector<Shape *> shapes;

EXTERN char * filen;

EXTERN int maxdepth;

EXTERN float attenuation[3]; //const, linear, quad

EXTERN vector<Light *> lights;
