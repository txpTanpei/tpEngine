#ifndef __RGBA_H__
#define __RGBA_H__

struct Rgba
{
public:
	Rgba(unsigned char r = 255,
	unsigned char g = 255,
	unsigned char b = 255,
	unsigned char a = 255);
	
	unsigned char _r;
	unsigned char _g;
	unsigned char _b;
	unsigned char _a;

};

#endif // !__RGBA_H__
