#pragma once


#define KINECT_COLOR_IMG_WIDTH  640
#define KINECT_COLOR_IMG_HEIGHT 480

typedef struct
{ 
    double cx, cy, fx, fy, scale;
} CAMERA_INTRINSIC_PARAMETERS;