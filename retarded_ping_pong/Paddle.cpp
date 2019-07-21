#include "Paddle.h"

Paddle::Paddle(VRInfo& vrInfo, VRInfo::EHand hand) :
	VRCapable{ vrInfo },
	PaddleRigitBodyConf(),
	btRigidBody(*info),
	m_name("Paddle"),
	m_shaderDesc(CompileGLShader(shaderName, vertexShaderContent, fragmentShaderContent)),
	m_matrixShaderLocation(GetShaderParamLocation(m_shaderDesc, "matrix")),
	m_hand{ hand }

{
	if (hand == VRInfo::Left) {
		vr::VRInput()->GetActionHandle("/actions/pingpong/out/Haptic_Left", &m_actionHaptic);
	}
	else {
		vr::VRInput()->GetActionHandle("/actions/pingpong/out/Haptic_Right", &m_actionHaptic);
	}

	GLfloat vertexData[] = {
	-1.0f,-1.0f,-1.0f, // triangle 1 : begin
	-1.0f,-1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, // triangle 1 : end
	1.0f, 1.0f,-1.0f, // triangle 2 : begin
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f, // triangle 2 : end
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f
	};


	m_vertexCount = sizeof(vertexData) / sizeof(float);
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertexCount * sizeof(float), vertexData, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);

	glBindVertexArray(0);
	glDisableVertexAttribArray(0);


	setRestitution(0.5);
	setCollisionFlags(btRigidBody::CollisionFlags::CF_KINEMATIC_OBJECT);
	setUserPointer((void*)(m_name.c_str()));
}


void Paddle::RenderScene(vr::Hmd_Eye nEye)
{
	glUseProgram(m_shaderDesc);
	Matrix4 matDeviceToTracking = m_vrInfo.m_rHand[m_hand].m_rmat4Pose;
	std::cout << "PADDLE" << std::endl;
	//vr::TrackedDevicePose_t pose;
	//m_vrInfo.m_pHMD->GetDeviceToAbsoluteTrackingPose(vr::TrackingUniverseOrigin::TrackingUniverseStanding, 0, &pose, 0);
	//pose.mDeviceToAbsoluteTracking;
	std::cout << "vr Matrix" << std::endl;
	std::cout << matDeviceToTracking << std::endl;
	btTransform mat;
	auto matDevicecopy = matDeviceToTracking;
	matDevicecopy = matDevicecopy.translate(Vector3(-paddleSize / 2, -paddleSize / 2, -paddleSize / 2));
	//mat.setFromOpenGLMatrix(matDevicecopy.get());
	mat.setFromOpenGLMatrix(matDevicecopy.get());
	getMotionState()->setWorldTransform(mat);
	std::cout << "bt Matrix" << std::endl;
	auto& origin = mat.getOrigin();
	std::cout << origin.getX() << " " << origin.getY() << " " << origin.getZ() << std::endl;

	Matrix4 matMVP;
	matMVP.scale(0.1f);
	matMVP = m_vrInfo.GetCurrentViewProjectionMatrix(nEye) * matDeviceToTracking * matMVP;

	glUniformMatrix4fv(m_matrixShaderLocation, 1, GL_FALSE, matMVP.get());
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);
	glBindVertexArray(0);
	glUseProgram(0);
}

void Paddle::HandleInput()
{
	bool collided = false;
	if (collided) {
		vr::VRInput()->TriggerHapticVibrationAction(m_actionHaptic, 0, 1, 4.f, 1.0f, vr::k_ulInvalidInputValueHandle);
	}
}
