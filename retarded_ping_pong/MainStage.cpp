#include "MainStage.h"

bool MainStage::CreateAllShaders()
{
	
	
	return false;
}

GLuint MainStage::getSceneShader()
{
	GLuint m_unSceneProgramID = CompileGLShader(
		"Scene",

		// Vertex Shader
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
		"}\n",

		// Fragment Shader
		"#version 410 core\n"
		"uniform sampler2D mytexture;\n"
		"in vec2 v2UVcoords;\n"
		"out vec4 outputColor;\n"
		"void main()\n"
		"{\n"
		"   outputColor = texture(mytexture, v2UVcoords);\n"
		"}\n"
	);
	return m_unSceneProgramID;
}

GLint MainStage::getSceneMatrixLocation(const GLuint shaderDesc, const std::string& paramName)
{
	GLint m_nSceneMatrixLocation = glGetUniformLocation(shaderDesc, paramName.c_str());
	if (m_nSceneMatrixLocation == -1)
	{
		dprintf("Unable to find matrix uniform in scene shader\n");
	}
	return m_nSceneMatrixLocation;
}

void MainStage::RenderScene(vr::Hmd_Eye nEye)
{
}
