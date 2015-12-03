#include <math.h>

#define TEXTURE_ERROR(msg)                         \
{                                                  \
    MessageBox(NULL, msg, "Error", MB_OK);         \
    return -1;                                     \
}                                                  

bool ispowerof2(int num)
{
    return !(num & (num - 1)) && num;
}

int gettexture(const char *filename)
{
    
    FILE *in;
    in = fopen(filename, "rb");
    if (!in) TEXTURE_ERROR("Cannot open texture file");
    
    gdImagePtr im;
    im = gdImageCreateFromJpeg(in);
    if (!im) TEXTURE_ERROR("Problem reading JPEG file");
    fclose(in);
    
    const int &width = im->sx;
    const int &height = im->sy;    
    
    if (!ispowerof2(height)) TEXTURE_ERROR("Height must be a power of 2");          
    if (!ispowerof2(width)) TEXTURE_ERROR("Width must be a power of 2");
    
    int MaxTextureSize = 0; 
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &MaxTextureSize);
    
    if (height > MaxTextureSize) TEXTURE_ERROR("Height is greater than maximum texture size");    
    if (width > MaxTextureSize) TEXTURE_ERROR("Width is greater than maximum texture size");
    
    unsigned char *imagedata = new unsigned char[width*height*3];
    
    for (int y = 0; y < height; y++)
    for (int x = 0; x < width; x++)
    {
        int rgb = gdImageGetPixel(im, x, y);
        int red = gdImageRed(im, rgb);
        int green = gdImageGreen(im, rgb);
        int blue = gdImageBlue(im, rgb);
        imagedata[y*width*3+x*3] = red;
        imagedata[y*width*3+x*3+1] = green;
        imagedata[y*width*3+x*3+2] = blue;
    }
    
    // Create The Texture
    GLuint mytexture;
    glGenTextures(1, &mytexture);					
    glBindTexture(GL_TEXTURE_2D, mytexture);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imagedata);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    delete[] imagedata;
    return mytexture;
}
