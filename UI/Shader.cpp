#include"include.h"
#include<assert.h>


ProgramID::ProgramID() : 
	_programID(-1),
	_vertex(-1),
	_fragment(-1)
{

}

bool ProgramID::createProgram(const char* vert, const char* frag)
{
	bool error = false;
	do {
		if (vert)
		{
			_vertex = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(_vertex, 1, &vert, 0);
			glCompileShader(_vertex);

			GLint compileStatus;
			glGetShaderiv(_vertex, GL_COMPILE_STATUS, &compileStatus);
			error = compileStatus == GL_FALSE;
			if (error)
			{
				GLchar message[256];
				glGetShaderInfoLog(_vertex, sizeof(message), 0, message);
				assert(message && 0 != 0);
				break;
			}
		}
		if (frag)
		{
			_fragment = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(_fragment, 1, &frag, 0);
			glCompileShader(_fragment);

			GLint compileStatus;
			glGetShaderiv(_fragment, GL_COMPILE_STATUS, &compileStatus);
			error = compileStatus == GL_FALSE;

			if (error)
			{
				GLchar message[256];
				glGetShaderInfoLog(_fragment, sizeof(message), 0, message);
				assert(message && 0 != 0);
				break;
			}
		}

		_programID = glCreateProgram();
		if (_vertex)
		{
			glAttachShader(_programID, _vertex);
		}
		if (_fragment)
		{
			glAttachShader(_programID, _fragment);
		}

		glLinkProgram(_programID);
		GLint linkStatus;
		glGetProgramiv(_programID, GL_LINK_STATUS, &linkStatus);
		error = linkStatus == GL_FALSE;
		if (error)
		{
			GLchar message[256];
			glGetProgramInfoLog(_programID, sizeof(message), 0, message);
			break;
		}
		glUseProgram(_programID);

	} while (false);

	if (error)  
	{
		//ÊÍ·Å×ÊÔ´
		if (_fragment)
		{
			glDeleteShader(_fragment);
			_fragment = -1;
		}
		if (_vertex)
		{
			glDeleteShader(_vertex);
			_vertex = -1;
		}
		if (_programID)
		{
			glDeleteProgram(_programID);
			_programID = 0;
		}
	}

	return true;
}

void ProgramID::begin()
{
	glUseProgram(_programID);
}

void ProgramID::end()
{
	glUseProgram(0);
}




//////////////////////////////////////////////////////
/////////////////////////ProgramID end////////////////
//////////////////////////////////////////////////////

PROGRAM_P2_C4::PROGRAM_P2_C4():
	_position(-1),
	_color(-1),
	_MVP(-1),
	_uv(-1),
	_texture(-1)
{

}
PROGRAM_P2_C4::~PROGRAM_P2_C4()
{
	_position = -1;
	_color = -1;
	_MVP = -1;
	_uv = -1;
	_texture = -1;
}

bool PROGRAM_P2_C4::initialize()
{
	const char* vs = 
	{
		"precision lowp float; "
		"uniform   mat4 _MVP;"
		"attribute vec2 _position;"
		"attribute vec2 _uv;"
		"attribute vec4 _color;"
		"varying   vec4 _outColor;"
		"varying   vec2 _outUV;"

		"void main()"
		"{"
		"   vec4    pos =   vec4(_position,0,1);"
		"   _outColor   =   _color;"
		"   _outUV      =   _uv;"
		"   gl_Position =   _MVP * pos;"
		"}"
	};

	const char* ps = 
	{
		"precision  lowp float; "
		"uniform   sampler2D _texture;\n"
		"varying   vec4      _outColor;\n"
		"varying   vec2      _outUV;\n"
		"void main()"
		"{"
		"   vec4    tColor  =   texture2D(_texture,_outUV);\n"
		"	if(tColor.a<0.1)"
		"		discard;"
		"   gl_FragColor    =   tColor * _outColor;\n"
		"}"
	};

	bool res = createProgram(vs, ps);
	if (res)
	{
		_position = glGetAttribLocation(_programID, "_position");
		_color = glGetAttribLocation(_programID, "_color");
		_uv = glGetAttribLocation(_programID, "_uv");
		_MVP = glGetUniformLocation(_programID, "_MVP");
		_texture = glGetUniformLocation(_programID, "_texture");
	}
	return res;
}

void PROGRAM_P2_C4::begin()
{
	glUseProgram(_programID);
	glEnableVertexAttribArray(_position);
	glEnableVertexAttribArray(_color);
	glEnableVertexAttribArray(_uv);
}

void PROGRAM_P2_C4::end()
{
	glDisableVertexAttribArray(_position);
	glDisableVertexAttribArray(_uv);
	glUseProgram(0);
}

