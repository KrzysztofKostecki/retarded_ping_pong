#pragma once

#include "RenderableInterface.h"
#include "RenderModel.h"
#include "MainStage.h"

#include <Matrices.h>
#include <vector>

//-----------------------------------------------------------------------------
// Purpose:
//------------------------------------------------------------------------------
class Application
{
public:
	Application();
	virtual ~Application();

	bool BInit();
	bool BInitGL();
	bool BInitCompositor();

	void Shutdown();

	void RunMainLoop();
	bool HandleInput();
	void ProcessVREvent(const vr::VREvent_t& event);
	void RenderFrame();

	bool SetupTexturemaps();

	void SetupScene();

	bool SetupStereoRenderTargets();
	void SetupCompanionWindow();
	void SetupCameras();

	void RenderStereoTargets();
	void RenderCompanionWindow();

	Matrix4 GetHMDMatrixProjectionEye(vr::Hmd_Eye nEye);
	Matrix4 GetHMDMatrixPoseEye(vr::Hmd_Eye nEye);
	Matrix4 GetCurrentViewProjectionMatrix(vr::Hmd_Eye nEye);
	void UpdateHMDMatrixPose();

	Matrix4 ConvertSteamVRMatrixToMatrix4(const vr::HmdMatrix34_t& matPose);

	bool CreateAllShaders();

	RenderModel* FindOrLoadRenderModel(const char* pchRenderModelName);

private:
	bool m_bDebugOpenGL;
	bool m_bVerbose;
	bool m_bPerf;
	bool m_bVblank;
	bool m_bGlFinishHack;

	RenderInfo m_renderInfo;
	VRInfo m_vrInfo;

private: // SDL bookkeeping
	SDL_Window* m_pCompanionWindow;
	uint32_t m_nCompanionWindowWidth;
	uint32_t m_nCompanionWindowHeight;

	SDL_GLContext m_pContext;

private: // OpenGL bookkeeping

	float m_fNearClip;
	float m_fFarClip;

	GLuint m_unCompanionWindowProgramID;
	GLuint m_unCompanionWindowVAO;
	GLuint m_glCompanionWindowIDVertBuffer;
	GLuint m_glCompanionWindowIDIndexBuffer;
	unsigned int m_uiCompanionWindowIndexSize;

	bool CreateFrameBuffer(int nWidth, int nHeight, FramebufferDesc& framebufferDesc);
};
