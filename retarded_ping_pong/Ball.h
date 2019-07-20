#pragma once
#include "RenderableInterface.h"
class Ball :
	public VRCapable
{
public:
	Ball(VRInfo& vrInfo) : VRCapable{ vrInfo } {}

	// Inherited via VRCapable
	void RenderScene(vr::Hmd_Eye nEye) override;
};

