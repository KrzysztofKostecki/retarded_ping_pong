//========= Copyright Retarded Corporation ============//

#include "Application.h"

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
	Application app;

	if (!app.BInit())
	{
		app.Shutdown();
		return 1;
	}

	app.RunMainLoop();
	app.Shutdown();

	return 0;
}
