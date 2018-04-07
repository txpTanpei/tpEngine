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
	//1.��ȡ ͼƬ�ĸ�ʽ
	FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(fileName, 0);
	//2.����ͼƬ
	FIBITMAP *dib = FreeImage_Load(fifmt, fileName, 0);
	int tmp = GL_RGB;
	if (fifmt == FIF_PNG)
	{
		//3.ת��Ϊrgb 8 * 3 = 24
		dib = FreeImage_ConvertTo32Bits(dib);
		tmp = GL_RGBA;
	}
	else
	{
		//3.ת��Ϊrgba 8 * 4 = 32
		dib = FreeImage_ConvertTo24Bits(dib);
	}

	//4.��ȡ����ָ��
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
	

	//����һ������ID
	glGenTextures(1, &textureId);

	//������
	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//��ͼƬrgb���ݴ��ݸ�OpenGL ES
	glTexImage2D(
		GL_TEXTURE_2D,  //ָ���Ƕ�άͼƬ
		0,              //�ƶ�Ϊ��һ�������������mipMap
		tmp,         //����ʹ�õĴ洢��ʽ
		width,          //�� 
		height,         //��
		0,              //ͼƬ�Ƿ��б�
		tmp,         //
		GL_UNSIGNED_BYTE,//���ݹ�ȥ�����ݸ�ʽ 8bit����
		pixels
	);
	//ͼƬ�����Ѿ����ݵ��Կ��ڴ��У��Ƿ�CPU�ڴ�ͼƬ�����ľ�� -->�ͷŲ��õ��ڴ�
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
			GL_TEXTURE_2D, //��άͼƬ
			index,         //�ڼ���
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