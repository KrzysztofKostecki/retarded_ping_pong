#pragma once

#include <GLIncludes.h>
#include <Matrices.h>
#include <openvr.h>




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

struct RenderableInterface {
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

	GLint m_nSceneMatrixLocation;
	GLint m_nControllerMatrixLocation;
	GLint m_nRenderModelMatrixLocation;

	uint32_t m_nRenderWidth;
	uint32_t m_nRenderHeight;
};

class VRCapable : public RenderableInterface {
protected:
	VRInfo& m_vrInfo;

public:

	VRCapable(VRInfo& vr) :  m_vrInfo{ vr }{}
};
