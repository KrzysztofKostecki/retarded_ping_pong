#pragma once

#include <bullet/btBulletCollisionCommon.h>
#include <bullet/btBulletDynamicsCommon.h>

#include "RenderableInterface.h"

struct PaddleRigitBodyConf {
	static constexpr btScalar paddleSize = 1.f;
	btRigidBody::btRigidBodyConstructionInfo* info;

	PaddleRigitBodyConf() {
		btCollisionShape* groundShape = new btBoxShape(btVector3(paddleSize, paddleSize, paddleSize));

		btTransform groundTransform;
		groundTransform.setIdentity();

		btScalar mass(1.0);
		btVector3 localInertia(0, 0, 0);
		groundShape->calculateLocalInertia(mass, localInertia);

		//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
		info = new btRigidBody::btRigidBodyConstructionInfo(mass, myMotionState, groundShape, localInertia);
	}
};


class Paddle :
	public VRCapable,
	public PaddleRigitBodyConf,
	public btRigidBody
{

public:
	Paddle(VRInfo& vrInfo, VRInfo::EHand hand);
	// Inherited via VRCapable
	void RenderScene(vr::Hmd_Eye nEye) override;
	void HandleInput() override;

private:
	GLuint m_shaderDesc;
	GLuint m_matrixShaderLocation;
	GLuint m_vbo;
	GLuint m_vao;
	GLuint m_vertexCount;
	Matrix4 m_position;
	std::string m_name;

	VRInfo::EHand m_hand;
	vr::VRActionHandle_t m_actionHaptic;
private:
	static constexpr const char* shaderName = "controller";
	static constexpr const char* vertexShaderContent =
		"#version 410\n"
		"uniform mat4 matrix;\n"
		"layout(location = 0) in vec4 position;\n"
		"layout(location = 1) in vec2 v2UVcoordsIn;\n"
		"layout(location = 2) in vec3 v3NormalIn;\n"
		"out vec2 v2UVcoords;\n"
		"void main()\n"
		"{\n"
		"	v2UVcoords = v2UVcoordsIn;\n"
		"	gl_Position = matrix * position;\n"
		"}\n";
	static constexpr const char* fragmentShaderContent =
		"#version 410 core\n"
		"uniform sampler2D mytexture;\n"
		"in vec2 v2UVcoords;\n"
		"out vec4 outputColor;\n"
		"void main()\n"
		"{\n"
		"   outputColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
		"}\n";
};

