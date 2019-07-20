#pragma once
#include "RenderableInterface.h"

class Paddle :
	public VRCapable
{

public:
	Paddle(VRInfo& vrInfo) :
		VRCapable{ vrInfo },
		m_shaderDesc(CompileGLShader(shaderName, vertexShaderContent, fragmentShaderContent)),
		m_matrixShaderLocation(GetShaderParamLocation(m_shaderDesc, "matrix")) 
	{
		vr::VRInput()->GetActionHandle("/actions/pingpong/out/Haptic_Left", &vrInfo.m_rHand[VRInfo::Left].m_actionHaptic);
		vr::VRInput()->GetActionHandle("/actions/pingpong/out/Haptic_Right", &vrInfo.m_rHand[VRInfo::Right].m_actionHaptic);
	}

	// Inherited via VRCapable
	void RenderScene(vr::Hmd_Eye nEye) override;
	void HandleInput() override;

private:
	GLuint m_shaderDesc;
	GLuint m_matrixShaderLocation;
private:
	static constexpr const char* shaderName = "controller";
	static constexpr const char* vertexShaderContent =
		"#version 410\n"
		"uniform mat4 matrix;\n"
		"layout(location = 0) in vec4 position;\n"
		"layout(location = 1) in vec3 v3ColorIn;\n"
		"out vec4 v4Color;\n"
		"void main()\n"
		"{\n"
		"	v4Color.xyz = v3ColorIn; v4Color.a = 1.0;\n"
		"	gl_Position = matrix * position;\n"
		"}\n";
	static constexpr const char* fragmentShaderContent =
		"#version 410\n"
		"in vec4 v4Color;\n"
		"out vec4 outputColor;\n"
		"void main()\n"
		"{\n"
		"   outputColor = v4Color;\n"
		"}\n";
};

