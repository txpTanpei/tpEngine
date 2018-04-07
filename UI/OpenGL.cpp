#include"include.h"
#include"tp_math.h"

OpenGL::OpenGL(HWND hWnd):
	_config(0),
	_surface(0),
	_context(0),
	_display(0),
	_hWnd(hWnd)
{

}


OpenGL::~OpenGL()
{
}

bool OpenGL::initOpenGL(int width, int height)
{
	m_nWidth = width;
	m_nHeigth = height;

	const EGLint attribs[] =
	{
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_BLUE_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_RED_SIZE, 8,
		EGL_DEPTH_SIZE,24,
		EGL_NONE
	};
	EGLint 	format(0);
	EGLint	numConfigs(0);
	EGLint  major;
	EGLint  minor;

	_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	eglInitialize(_display, &major, &minor);
	eglChooseConfig(_display, attribs, &_config, 1, &numConfigs);
	eglGetConfigAttrib(_display, _config, EGL_NATIVE_VISUAL_ID, &format);
	_surface = eglCreateWindowSurface(_display, _config, _hWnd, NULL);
	EGLint attr[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };
	_context = eglCreateContext(_display, _config, 0, attr);
	if (eglMakeCurrent(_display, _surface, _surface, _context) == EGL_FALSE)
	{
		return false;
	}

	eglQuerySurface(_display, _surface, EGL_WIDTH, &m_nWidth);
	eglQuerySurface(_display, _surface, EGL_HEIGHT, &m_nHeigth);

	if (!_shader.initialize())
	{
		return false;
	}

	_texture2d.loadTexture("ui/grass.png");

	/*const char*   files[] =
	{
		"ui/tex33X32.bmp",
		"ui/tex16X16.bmp",
		"ui/tex8x8.bmp",
		"ui/tex4x4.bmp",
		"ui/tex2X2.bmp",
		"ui/tex1x1.bmp",
	};
	_texture2d.loadMinMap(files, 6);*/

	return  true;
}
void OpenGL::destory()
{
	glDeleteTextures(1, &_texture2d._textureId);

	if (_display != EGL_NO_DISPLAY)
	{
		eglMakeCurrent(_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		if (_context != EGL_NO_CONTEXT)
		{
			eglDestroyContext(_display, _context);
		}
		if (_surface != EGL_NO_SURFACE)
		{
			eglDestroySurface(_display, _surface);
		}
		eglTerminate(_display);
	}

	_display = EGL_NO_DISPLAY;
	_context = EGL_NO_CONTEXT;
	_surface = EGL_NO_SURFACE;

}

void OpenGL::render()
{
	_shader.begin();
	_camera.updateCamera(0.016f);
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, m_nWidth, m_nHeigth);
	draw();
	//双缓存
	eglSwapBuffers(_display, _surface);
	_shader.end();
}

void OpenGL::draw()
{
	//生成观察矩阵

	//观察矩阵
	Matrix4x4 matView;
	matView.lookAt(_camera._eye, _camera._look, _camera._up);

	//世界矩阵
	Matrix4x4 matWorld;
	matWorld.identity();

	//投影矩阵
	Matrix4x4 matProj;
	matProj.perspective(45.0f, (GLfloat)m_nWidth / (GLfloat)m_nHeigth, 0.1f, 100.0f);
	
	Matrix4x4 mat;
	mat.ortho(0, float(m_nWidth), float(m_nHeigth), 0, -100.0f, 100);

	float x = 100;
	float y = 100;
	float w = 300;
	float h = 300;

	Rgba rgba[]=
	{
		Rgba(255,255,255,255),
		Rgba(255,255,255,255),
		Rgba(255,255,255,255),
		Rgba(255,255,255,255),
	};

	
	
	Vector2 pos[] = 
	{
		Vector2(x,y),
		Vector2(x+w,y),
		Vector2(x,y+h),
		Vector2(x+w,y+h),
	};

	Vector2 uvPos[] =
	{
		Vector2(0,0),
		Vector2(1, 0.0f),
		Vector2(0, 1),
		Vector2(1, 1),

	};

	float   gSize = 100;
	float   gPos = -5;
	float   rept = 100;
	/*
	Vector3 pos[] =
	{
		Vector3(-gSize, gPos,-gSize),
		Vector3(gSize, gPos,-gSize),
		Vector3(gSize, gPos, gSize),
		Vector3(-gSize, gPos, gSize),
	};

	Vector2 uvPos[] =
	{
		Vector2(0,0),
		Vector2(rept, 0.0f),
		Vector2(rept, rept),
		Vector2(0.0f, rept),

	};
	*/
	
	Matrix4x4 matRo;
	static float angle = 1;
	Vector3 vec3;
	vec3.z = 1;

	Matrix4x4 matTran;
	Vector3 _vec;
	_vec.x = -5;
	_vec.y = -5;
	matTran.project(_vec);

	//matRo.rotate(vec3, angle);
	Matrix4x4 matMVP = mat * matRo;// *matTran);
	//angle += 1;


	//Matrix4x4   MVP = matProj * matView * matWorld;

	//启用混合
	//glEnable(GL_ALPHA);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindTexture(GL_TEXTURE_2D, _texture2d._textureId);

	glUniformMatrix4fv(_shader._MVP, 1, false, &(matMVP.value[0][0]));
	glUniform4f(_shader._color, 1, 0, 0, 1);
	glVertexAttribPointer(_shader._position, 2, GL_FLOAT, false, sizeof(Vector2), pos);
	glVertexAttribPointer(_shader._uv, 2, GL_FLOAT, false, sizeof(Vector2), uvPos);
	glVertexAttribPointer(_shader._color, 4, GL_UNSIGNED_BYTE, true, sizeof(Rgba), rgba);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}



//////////////////////////////////////end class OpenGL/////////