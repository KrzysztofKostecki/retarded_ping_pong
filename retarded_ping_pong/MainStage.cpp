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
		
	);
	return m_unSceneProgramID;
}


void MainStage::RenderScene(vr::Hmd_Eye nEye)
{
}
