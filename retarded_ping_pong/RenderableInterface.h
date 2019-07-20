#pragma once

#include <GLIncludes.h>
#include <Matrices.h>
#include <openvr.h>


void ThreadSleep(unsigned long nMilliseconds)
{
#if defined(_WIN32)
	::Sleep(nMilliseconds);
#elif defined(POSIX)
	usleep(nMilliseconds * 1000);
#endif
}

//-----------------------------------------------------------------------------
// Purpose: Outputs a set of optional arguments to debugging output, using
//          the printf format setting specified in fmt*.
//-----------------------------------------------------------------------------
void dprintf(const char* fmt, ...)
{
	va_list args;
	char buffer[2048];

	va_start(args, fmt);
	vsprintf_s(buffer, fmt, args);
	va_end(args);

	//if (g_bPrintf)
	printf("%s", buffer);

	OutputDebugStringA(buffer);
}


struct VertexDataScene
{
	Vector3 position;
	Vector2 texCoord;
};

struct VertexDataWindow
{
	Vector2 position;
	Vector2 texCoord;

	VertexDataWindow(const Vector2& pos, const Vector2 tex) : position(pos), texCoord(tex) {	}
};

struct FramebufferDesc
{
	GLuint m_nDepthBufferId;
	GLuint m_nRenderTextureId;
	GLuint m_nRenderFramebufferId;
	GLuint m_nResolveTextureId;
	GLuint m_nResolveFramebufferId;
};

struct RenderInfo {
	GLint m_nSceneMatrixLocation;
	GLint m_nControllerMatrixLocation;
	GLint m_nRenderModelMatrixLocation;

	uint32_t m_nRenderWidth;
	uint32_t m_nRenderHeight;

};

struct RenderableInterface {
	RenderInfo& m_renderInfo;
	RenderableInterface(RenderInfo& renderInfo) : m_renderInfo{ renderInfo } {}
	static GLuint CompileGLShader(const char* pchShaderName, const char* pchVertexShader, const char* pchFragmentShader);
	static GLint GetShaderParamLocation(const GLuint shaderDesc, const std::string& paramName);
	virtual void RenderScene(vr::Hmd_Eye nEye) = 0;
};

struct VRInfo {
	vr::IVRSystem* m_pHMD;
	std::string m_strDriver;
	std::string m_strDisplay;
	vr::TrackedDevicePose_t m_rTrackedDevicePose[vr::k_unMaxTrackedDeviceCount];
	Matrix4 m_rmat4DevicePose[vr::k_unMaxTrackedDeviceCount];

	struct ControllerInfo_t
	{
		vr::VRInputValueHandle_t m_source = vr::k_ulInvalidInputValueHandle;
		vr::VRActionHandle_t m_actionPose = vr::k_ulInvalidActionHandle;
		vr::VRActionHandle_t m_actionHaptic = vr::k_ulInvalidActionHandle;
		Matrix4 m_rmat4Pose;
		RenderModel* m_pRenderModel = nullptr;
		std::string m_sRenderModelName;
		bool m_bShowController;
	};

	enum EHand
	{
		Left = 0,
		Right = 1,
	};
	ControllerInfo_t m_rHand[2];

	int m_iTrackedControllerCount;
	int m_iTrackedControllerCount_Last;
	int m_iValidPoseCount;
	int m_iValidPoseCount_Last;
	bool m_bShowCubes;
	Vector2 m_vAnalogValue;

	std::string m_strPoseClasses;                            // what classes we saw poses for this frame
	char m_rDevClassChar[vr::k_unMaxTrackedDeviceCount];   // for each device, a character representing its class

	Matrix4 m_mat4HMDPose;
	Matrix4 m_mat4eyePosLeft;
	Matrix4 m_mat4eyePosRight;

	Matrix4 m_mat4ProjectionCenter;
	Matrix4 m_mat4ProjectionLeft;
	Matrix4 m_mat4ProjectionRight;

	FramebufferDesc leftEyeDesc;
	FramebufferDesc rightEyeDesc;
};

class VRCapable : public RenderableInterface {
protected:
	VRInfo& m_vrInfo;

public:

	VRCapable(RenderInfo& renderInfo, VRInfo& vr) : RenderableInterface{ renderInfo
	}, m_vrInfo{ vr }{}
};
