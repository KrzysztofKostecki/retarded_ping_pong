#pragma once
#include "RenderableInterface.h"
class Ball :
	public VRCapable
{
public:
	Ball(RenderInfo& renderInfo, VRInfo& vrInfo) : VRCapable{ renderInfo, vrInfo } {}

	// Inherited via VRCapable
	void RenderScene(vr::Hmd_Eye nEye) override;
};

