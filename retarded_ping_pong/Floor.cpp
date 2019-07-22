#include "Floor.h"

Floor::Floor(VRInfo& vrInfo) :
	VRCapable{ vrInfo },
	FloorRigitBodyConf(),
	btRigidBody(*info),
	m_name("Floor"),
	m_shaderDesc(CompileGLShader(shaderName, vertexShaderContent, fragmentShaderContent)),
	m_matrixShaderLocation(GetShaderParamLocation(m_shaderDesc, "matrix")) 
{

	GLfloat vertexData[] = {
		-20.0f,-20.0f,-20.0f, // triangle 1 : begin
		-20.0f,-20.0f, 20.0f,
		-20.0f, 20.0f, 20.0f, // triangle 1 : end
		20.0f, 20.0f,-20.0f, // triangle 2 : begin
		-20.0f,-20.0f,-20.0f,
		-20.0f, 20.0f,-20.0f, // triangle 2 : end
		20.0f,-20.0f, 20.0f,
		-20.0f,-20.0f,-20.0f,
		20.0f,-20.0f,-20.0f,
		20.0f, 20.0f,-20.0f,
		20.0f,-20.0f,-20.0f,
		-20.0f,-20.0f,-20.0f,
		-20.0f,-20.0f,-20.0f,
		-20.0f, 20.0f, 20.0f,
		-20.0f, 20.0f,-20.0f,
		20.0f,-20.0f, 20.0f,
		-20.0f,-20.0f, 20.0f,
		-20.0f,-20.0f,-20.0f,
		-20.0f, 20.0f, 20.0f,
		-20.0f,-20.0f, 20.0f,
		20.0f,-20.0f, 20.0f,
		20.0f, 20.0f, 20.0f,
		20.0f,-20.0f,-20.0f,
		20.0f, 20.0f,-20.0f,
		20.0f,-20.0f,-20.0f,
		20.0f, 20.0f, 20.0f,
		20.0f,-20.0f, 20.0f,
		20.0f, 20.0f, 20.0f,
		20.0f, 20.0f,-20.0f,
		-20.0f, 20.0f,-20.0f,
		20.0f, 20.0f, 20.0f,
		-20.0f, 20.0f,-20.0f,
		-20.0f, 20.0f, 20.0f,
		20.0f, 20.0f, 20.0f,
		-20.0f, 20.0f, 20.0f,
		20.0f,-20.0f, 20.0f
	};

	m_vertexCount = sizeof(vertexData) / sizeof(float);
	glGenVertexArrays( 1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers( 1, &m_vbo);
	glBindBuffer( GL_ARRAY_BUFFER, m_vbo);
	glBufferData( GL_ARRAY_BUFFER, m_vertexCount*sizeof(float), vertexData, GL_STATIC_DRAW);

	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3 , nullptr);

	glBindVertexArray( 0 );
	glDisableVertexAttribArray(0);

	setRestitution(0.1);
	setUserPointer((void*)(m_name.c_str()));
}

Floor::~Floor() {

}

void Floor::RenderScene(vr::Hmd_Eye nEye)
{
	btTransform& mat = getWorldTransform();
	float raw[16];
	mat.getOpenGLMatrix(raw);
	m_position.set(raw);
	
	m_position.translate(Vector3(0.0, -20.0, 0.0));
	m_position = m_vrInfo.GetCurrentViewProjectionMatrix(nEye) * m_position;

	glUseProgram(m_shaderDesc);
	glUniformMatrix4fv(m_matrixShaderLocation, 1, GL_FALSE, m_position.get());
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);
	glBindVertexArray(0);
	glUseProgram(0);

}

void Floor::HandleInput()
{
}
