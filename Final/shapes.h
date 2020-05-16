//
// shapes.h
//
// Prototypes for shape-drawing functions.
//
// Students should not modify this file.
//

#ifndef _SHAPES_H_
#define _SHAPES_H_

// Macros for object and shading selection
#define OBJ_BACKGROUND	0
#define OBJ_FENCE		1
#define OBJ_GROUND      2
#define OBJ_TARDIS      3

#define SHADE_FLAT       0
#define SHADE_NOT_FLAT   1

// Prototypes
void makeShape( int choice, int shadingType );

#endif
