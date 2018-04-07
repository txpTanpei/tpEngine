#ifndef __OPENG_H__
#define __OPENG_H__

#include<egl\egl.h>
#include<gles2\gl2.h>
#include<windows.h>

#include "Shader.h"
#include "Texture2D.h"
#include "Camera.h"

class OpenGL
{
public:
	OpenGL(HWND hWnd);
	virtual ~OpenGL();
	virtual bool initOpenGL(int width,int height);
	virtual void destory();
	virtual void render();
	virtual void draw();
private:
	int m_nWidth;
	int m_nHeigth;

	HWND _hWnd;

	//opengl
	EGLConfig  _config;
	EGLSurface _surface;
	EGLContext _context;
	EGLDisplay _display;

	//shader
	PROGRAM_P2_C4 _shader;
	//PROGRAM_P2_C4_ _shader;

	//texture
	Texture2D _texture2d;
	Camera _camera;
}; //end class OpenGL


#endif // !1__OPENG_H__