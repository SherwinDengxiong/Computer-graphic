//
//  lightingParams.h
//
//  Created by Joe Geigel on 1/23/13.
//

#ifndef _LIGHTINGPARAMS_H_
#define _LIGHTINGPARAMS_H_

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#ifdef WIN32
#include <windows.h>
#endif
#include <GL/glew.h>
#include <GL/gl.h>
#endif

void setUpPhong( GLuint program, int object );

#endif
