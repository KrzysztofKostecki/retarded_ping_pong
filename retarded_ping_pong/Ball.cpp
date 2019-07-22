#include "Ball.h"

Ball::Ball(VRInfo& vrInfo) :
	VRCapable{ vrInfo },
	BallRigitBodyConf(),
	btRigidBody(*info),
	m_name("Ball"),
	m_shaderDesc(CompileGLShader(shaderName, vertexShaderContent, fragmentShaderContent)),
	m_matrixShaderLocation(GetShaderParamLocation(m_shaderDesc, "matrix"))
{

	GLfloat vertexData[] = {
		-1.0f,-1.0f,-1.0f, // triangle 1 : begin
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, // triangle 1 : end
		1.0f, 1.0f,-1.0f, // triangle 2 : begin
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f, // triangle 2 : end
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
	};

	m_vertexCount = sizeof(vertexData) / sizeof(float);
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertexCount * sizeof(float), vertexData, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);

	glBindVertexArray(0);
	glDisableVertexAttribArray(0);

	setRestitution(0.9);
	//setContactStiffnessAndDamping(1.0, 1.0);
	//setDamping(.5f, .5f);
	setUserIndex(-1);
	setUserPointer((void*)(m_name.c_str()));

}

Ball::~Ball() {

}

void Ball::RenderScene(vr::Hmd_Eye nEye)
{
	btTransform& mat = getWorldTransform();
	auto& origin = mat.getOrigin();
	float raw[16];
	mat.getOpenGLMatrix(raw);
	m_position.set(raw);
	m_position.scale(0.2f);
	m_position = m_vrInfo.GetCurrentViewProjectionMatrix(nEye) * m_position;
	glUseProgram(m_shaderDesc);
	glUniformMatrix4fv(m_matrixShaderLocation, 1, GL_FALSE, m_position.get());
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);
	glBindVertexArray(0);
	glUseProgram(0);

}

void Ball::HandleInput()
{
}
