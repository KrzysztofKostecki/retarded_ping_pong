#pragma once
#include "RenderableInterface.h"
class Ball :
	public VRCapable
{
public:
	Ball(VRInfo& vrInfo);
	~Ball();

	// Inherited via VRCapable
	void RenderScene(vr::Hmd_Eye nEye) override;
	void HandleInput() override;

private:
	GLuint m_vbo;
	GLuint m_vao;
	GLuint m_vertexCount;
	Matrix4 m_position;

private:
	GLuint m_shaderDesc;
	GLint m_matrixShaderLocation;

private:
	static constexpr const char* shaderName = "ball";
	static constexpr const char* vertexShaderContent =
		"#version 410\n"
		"uniform mat4 matrix;\n"
		"layout(location = 0) in vec4 position;\n"
		"layout(location = 1) in vec2 v2UVcoordsIn;\n"
		"layout(location = 2) in vec3 v3NormalIn;\n"
		"out vec2 v2UVcoords;\n"
		"void main()\n"
		"{\n"
		"	v2UVcoords = v2UVcoordsIn;\n"
		"	gl_Position = matrix * position;\n"
		"}\n";
	static constexpr const char* fragmentShaderContent =
		"#version 410 core\n"
		"uniform sampler2D mytexture;\n"
		"in vec2 v2UVcoords;\n"
		"out vec4 outputColor;\n"
		"void main()\n"
		"{\n"
		"   outputColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
		"}\n";
};

