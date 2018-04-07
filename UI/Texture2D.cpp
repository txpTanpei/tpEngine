#include "Texture2D.h"



Texture2D::Texture2D()
	:_textureId(0)
{
}

Texture2D::~Texture2D()
{
}


unsigned Texture2D::loadTexture(const char* fileName)
{

	unsigned textureId = 0;
	//1.获取 图片的格式
	FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(fileName, 0);
	//2.加载图片
	FIBITMAP *dib = FreeImage_Load(fifmt, fileName, 0);
	int tmp = GL_RGB;
	if (fifmt == FIF_PNG)
	{
		//3.转化为rgb 8 * 3 = 24
		dib = FreeImage_ConvertTo32Bits(dib);
		tmp = GL_RGBA;
	}
	else
	{
		//3.转化为rgba 8 * 4 = 32
		dib = FreeImage_ConvertTo24Bits(dib);
	}

	//4.获取数据指针
	BYTE *pixels = (BYTE*)FreeImage_GetBits(dib);

	int width = FreeImage_GetWidth(dib);
	int height = FreeImage_GetHeight(dib);

	if (fifmt == FIF_PNG)
	{
		//bgra  --> rgba
		for (int i = 0; i < width * height * 4; i += 4)
		{
			BYTE temp = pixels[i];
			pixels[i] = pixels[i + 2];
			pixels[i + 2] = temp;

		}
	}
	else
	{
		//bgr  --> rgb
		for (int i = 0; i < width * height * 3; i += 3)
		{
			BYTE temp = pixels[i];
			pixels[i] = pixels[i + 2];
			pixels[i + 2] = temp;

		}
	}
	

	//产生一个纹理ID
	glGenTextures(1, &textureId);

	//绑定纹理
	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//将图片rgb数据传递个OpenGL ES
	glTexImage2D(
		GL_TEXTURE_2D,  //指定是二维图片
		0,              //制定为第一级，纹理可以做mipMap
		tmp,         //纹理使用的存储格式
		width,          //宽 
		height,         //高
		0,              //图片是否有边
		tmp,         //
		GL_UNSIGNED_BYTE,//传递过去的数据格式 8bit数组
		pixels
	);
	//图片数据已经传递到显卡内存中，是否CPU内存图片操作的句柄 -->释放不用的内存
	FreeImage_Unload(dib);
	_textureId = textureId;
	return textureId;
	
}

unsigned Texture2D::loadMinMap(const char* fileNames[], int size)
{
	unsigned textureId = 0;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	for (int index = 0; index < size; index++)
	{
		FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(fileNames[index]);
		FIBITMAP *dib = FreeImage_Load(fifmt, fileNames[index], 0);
		dib = FreeImage_ConvertTo32Bits(dib);

		BYTE * pixels = (BYTE*)FreeImage_GetBits(dib);
		int width = FreeImage_GetWidth(dib);
		int height = FreeImage_GetHeight(dib);

		for (int i = 0; i < width * height *4; i+=4)
		{
			BYTE temp = pixels[i];
			pixels[i] = pixels[i + 2];
			pixels[i + 2] = temp;
		}
		glTexImage2D(
			GL_TEXTURE_2D, //二维图片
			index,         //第几级
			GL_RGBA,
			width,
			height,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			pixels
		);
		FreeImage_Unload(dib);
	}
	_textureId = textureId;
	return textureId;
}