//========= Copyright Retarded Corporation ============//

#include "Application.h"

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
	VRInfo vrInfo;
	RenderInfo renderInfo;
	Application mainStage;

	if (!mainStage.BInit())
	{
		mainStage.Shutdown();
		return 1;
	}

	mainStage.RunMainLoop();

	mainStage.Shutdown();

	return 0;
}
