#ifndef __SHADER_H__
#define __SHADER_H__

class ProgramID
{
public:
	ProgramID();
	bool createProgram(const char* vert, const char* frag);
	virtual void begin();
	virtual void end();
public :
	//用来标记shader的ID
	int _programID;
	int _vertex;
	int _fragment;
}; //end class ProgramID;

class PROGRAM_P2_C4 : public ProgramID
{
public:
	PROGRAM_P2_C4();
	~PROGRAM_P2_C4();
	virtual bool initialize();
	virtual void begin();
	virtual void end();

public:
	typedef int attribute;
	typedef int uniform;
public :
	//顶点索引
	attribute _position;
	//颜色索引
	attribute _color;
	//UV坐标
	attribute _uv;
	//model view project matrix
	uniform _MVP;
	//texture
	uniform _texture;
}; //end class PROGRAM_P2_C4

#endif // end __SHADER_H__
