// Thanks to Ben Humphrey at Game Tutorials for his OpenGL image loading code. 

#ifndef _TEXTURE_H
#define _TEXTURE_H

#include "jpeglib.h"


#define TGA_RGB		 2
#define TGA_A		 3
#define TGA_RLE		10

struct tImage
{
	int channels;
	int sizeX;
	int sizeY;
	unsigned char *data;
};

// This function loads BMP, JPG and TGA.
bool Load_Texture(UINT &texture, LPSTR strFileName);

// This Loads And Returns The BMP Image Data
tImage *LoadBMP(const char *strFileName);

// This Loads And Returns The JPG Image Data
tImage *LoadJPG(const char *strFileName);

// This Loads And Returns The TGA Image Data
tImage *LoadTGA(const char *strFileName);


#endif
