#ifndef _VARS_HPP_
#define _VARS_HPP_

#include "header.hpp"

extern GLboolean speed_test;
extern GLboolean use_vertex_arrays;

extern GLboolean doubleBuffer;

extern GLboolean smooth;
extern GLboolean lighting;

#ifndef MAXVERTS
#define MAXVERTS 10000
#endif

extern GLfloat verts[MAXVERTS][3];
extern GLfloat norms[MAXVERTS][3];
extern GLint numverts;

extern GLfloat xrot;
extern GLfloat yrot;

#endif // _VARS_HPP_
