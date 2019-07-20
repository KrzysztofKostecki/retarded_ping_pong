#include "MainStage.h"



void MainStage::RenderScene(vr::Hmd_Eye nEye)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glUseProgram(m_shaderDesc);

	m_ball->RenderScene(nEye);

	glUseProgram(0);
}

void MainStage::HandleInput()
{
}
