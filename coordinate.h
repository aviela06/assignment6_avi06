#ifndef COORDINATE_H
#define COORDINATE_H

struct _coordinate // defining coordinate structure
{
    float x; // x coordinate
    float y; // y coordinate
    int coord_id; // ID number
    struct _coordinate *next; // next node pointer
    struct _coordinate *previous; // previous node pointer
};
typedef struct _coordinate Coordinate; // changing structure name to Coordinate

#endif
