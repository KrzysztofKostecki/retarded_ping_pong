#pragma once 

#include "RenderableInterface.h"

class MainStage : public VRCapable {

public:
	MainStage(RenderInfo& renderInfo, VRInfo& vrInfo) : 
		VRCapable{ renderInfo, vrInfo }, 
		m_shaderDesc(CompileGLShader(shaderName, vertexShaderContent, fragmentShaderContent)), 
		m_matrixShaderLocation(GetShaderParamLocation(m_shaderDesc, "matrix"))  
	{
	}

	// Inherited via VRCapable
	void RenderScene(vr::Hmd_Eye nEye) override;


private:
	GLuint m_shaderDesc;
	GLuint m_matrixShaderLocation;

private:
	static constexpr const char* shaderName = "scene";
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
		"   outputColor = texture(mytexture, v2UVcoords);\n"
		"}\n";
};