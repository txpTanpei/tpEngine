#ifndef __TEXTURE2D_H__
#define __TEXTURE2D_H__

#include<FreeImage.h>
#include<gles2\gl2.h>
//#include<egl\egl.h>
//#include<gl>


class Texture2D
{
public:
	Texture2D();
	~Texture2D();
	//º”‘ÿŒ∆¿Ì
	virtual unsigned loadTexture(const char* fileName);
	virtual unsigned loadMinMap(const char* fileNames[], int size);
public:
	unsigned _textureId;

}; //end class Texture2D

#endif // !__TEXTURE2D_H__



