#include "MainStage.h"



void MainStage::RenderScene(vr::Hmd_Eye nEye)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glUseProgram(m_shaderDesc);
	//glUniformMatrix4fv(m_matrixShaderLocation, 1, GL_FALSE, m_vrInfo.GetCurrentViewProjectionMatrix(nEye).get());

	m_ball->RenderScene(nEye);

	glUseProgram(0);
}
