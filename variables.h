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

// Lighting parameter array, similar to that in the fragment shader
const int numLights = 10;
EXTERN float lightposn[4 * numLights];  // Light Positions
EXTERN float lightcolor[4 * numLights]; // Light Colors
EXTERN float lightransf[4 * numLights]; // Lights transformed by modelview
EXTERN int numused;                     // How many lights are used

// Materials (read from file)
// With multiple objects, these are colors for each.
EXTERN float ambient[4];
EXTERN float diffuse[4];
EXTERN float specular[4];
EXTERN float emission[4];
EXTERN float shininess;

//Define vertices
EXTERN int maxverts;
EXTERN vector<vec4> vertices;
EXTERN vector<Shape *> shapes;
