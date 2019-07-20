#include "MainStage.h"



void MainStage::RenderScene(vr::Hmd_Eye nEye)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	// TODO: render stuff in scene

	glUseProgram(0);
}
