#pragma once 
#include <vector>
#include <bullet/btBulletCollisionCommon.h>
#include <bullet/btBulletDynamicsCommon.h>

#include "RenderableInterface.h"
#include "Ball.h"
#include "Paddle.h"
#include "Floor.h"

class MainStage : public VRCapable{

public:
	MainStage(VRInfo& vrInfo);

	// Inherited via VRCapable
	void RenderScene(vr::Hmd_Eye nEye) override;
	void HandleInput() override;

private:
	bool MainStage::checkCollisions();

private:
	std::unique_ptr<Ball> m_ball;
	std::unique_ptr<Paddle> m_paddle1;
	std::unique_ptr<Paddle> m_paddle2;
	std::vector<std::unique_ptr<Ball>> m_balls;
	std::unique_ptr<Floor> m_floor;

private:
	std::unique_ptr<btDefaultCollisionConfiguration> m_collisionConfiguration;
	std::unique_ptr<btCollisionDispatcher> m_dispatcher;
	std::unique_ptr<btBroadphaseInterface> m_overlappingPairCache;
	std::unique_ptr<btSequentialImpulseConstraintSolver> m_solver;
	std::unique_ptr<btDiscreteDynamicsWorld> m_dynamics_world;

private:
	GLuint m_shaderDesc;
	GLint m_matrixShaderLocation;

private:
	static constexpr const char* shaderName = "scene";
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
		"   outputColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
		"}\n";
};