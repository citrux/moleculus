#ifndef _IMAGE_H
#define _IMAGE_H

#include <stdio.h>
#include <string.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include "struct.h"

typedef struct {
	int pallete;                // pallete type
	int bpp;                    // bits per pixel
	int width;                  // image width in pixels
	int height;                 // image height in pixels
	int id;                     // texture id
	char *data;                 // pixel array
} texture_image;

typedef struct {
	char  identsize;            // size of ID field that follows 18 byte header (0 usually)
    char  colourMapType;        // type of colour map 0=none, 1=has palette
    char  imageType;            // type of image 0=none,1=indexed,2=rgb,3=grey,+8=rle packed

    short colourMapStart;       // first colour map entry in palette
    short colourMapLength;      // number of colours in palette
    char  colourMapBits;        // number of bits per palette entry 15,16,24,32

    short xstart;               // image x origin
    short ystart;               // image y origin
    short width;                // image width in pixels
    short height;               // image height in pixels
    char  bits;                 // image bits per pixel 8,16,24,32
    char  descriptor;           // image descriptor bits (vh flip bits)
} TGA_HEADER;

typedef struct {
	// BMP HEADER
	short magic;                 // magic number "BM"
	unsigned int bmp_size;       // size of bmp file
	unsigned int reserved;       // application specific
	unsigned int bmp_offset;     // offset where the pixel array can be found

	// DIB HEADER
	unsigned int dib_size;       // number of bytes in the DIB header
	unsigned int width;          // image width in pixels
	unsigned int height;         // image height in pixels
	short planes;                // number of color planes being used
	short bpp;                   // image bits per pixel
	unsigned int compression;    // pixel compression
	unsigned int data_size;      // size of the raw data in the pixel array
	unsigned int h_resolution;   // horizontal resolution of the image
	unsigned int v_resolution;   // vertical resolution of the image
	unsigned int pallete;        // number of colors in the palette
	unsigned int colors;         // important colors
} BMP_HEADER;

enum {
	WE_FMT_NULL = 0,
	WE_FMT_TGA,
	WE_FMT_BMP
};

/* bmp compresion const */
enum {
    WE_BI_RGB = 0,
    WE_BI_RLE8, 
    WE_BI_RLE4,
    WE_BI_BITFIELDS,
    WE_BI_JPEG,
    WE_BI_PNG,
    WE_BI_ALPHABITFIELDS,
};

/* we_image_format: get file format */
int we_image_format(char *file);

/* we_image_load: load support image format [bmp, tga] */
int we_image_load(texture_image *tex, char *file);

/* we_image_load_bmp: load bmp image */
int we_image_load_bmp(texture_image *tex, char *file);

/* we_image_load_tga: load tga image */
int we_image_load_tga(texture_image *tex, char *file);

/* we_image_write: write image to file [bmp, tga] */
int we_image_write(char *file);

/* we_image_generate: simply function to generate OpenGL texture */
void we_image_generate(texture_image *tex);

extern void *we_malloc(size_t size);
extern void we_free(void *ptr);

#endif
