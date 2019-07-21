#include "MainStage.h"


MainStage::MainStage(VRInfo& vrInfo) :
	VRCapable{ vrInfo },
	m_shaderDesc(CompileGLShader(shaderName, vertexShaderContent, fragmentShaderContent)),
	m_matrixShaderLocation(GetShaderParamLocation(m_shaderDesc, "matrix")),
	m_ball(new Ball(m_vrInfo)),
	m_paddle1(new Paddle(m_vrInfo, VRInfo::Left)),
	m_paddle2(new Paddle(m_vrInfo, VRInfo::Right)),
	m_floor(new Floor(m_vrInfo))
{
	m_collisionConfiguration = std::make_unique <btDefaultCollisionConfiguration>();
	m_dispatcher = std::make_unique<btCollisionDispatcher>(m_collisionConfiguration.get());
	m_overlappingPairCache = std::make_unique<btDbvtBroadphase>();
	m_solver = std::make_unique<btSequentialImpulseConstraintSolver>();
	m_dynamics_world = std::make_unique<btDiscreteDynamicsWorld>(m_dispatcher.get(), m_overlappingPairCache.get(), m_solver.get(), m_collisionConfiguration.get());
	m_dynamics_world->setGravity(btVector3(0, -10, 0));

	//m_dynamics_world->addRigidBody(m_ball.get());
	m_dynamics_world->addRigidBody(m_paddle1.get());
	//m_dynamics_world->addRigidBody(m_paddle2.get());
	m_dynamics_world->addRigidBody(m_floor.get());
	
	for (std::size_t i = 0; i < 2; i++) {
		m_balls.push_back(std::make_unique<Ball>(m_vrInfo));
		btTransform mat;
		m_balls.back()->getMotionState()->getWorldTransform(mat);
		//mat.setOrigin(btVector3 (15 + (2 * i), 15 + (2*i), 15 + (2 * i)));
		m_balls.back()->getMotionState()->setWorldTransform(mat);

		m_dynamics_world->addRigidBody(m_balls.back().get());
	}
}


void MainStage::RenderScene(vr::Hmd_Eye nEye)
{
	m_dynamics_world->updateAabbs();
	m_dynamics_world->stepSimulation(1.f / 60.f, 100);
	bool collisions = checkCollisions();

	//print positions of all objects
	for (int j = m_dynamics_world->getNumCollisionObjects() - 1; j >= 0; j--)
	{
		btCollisionObject* obj = m_dynamics_world->getCollisionObjectArray()[j];
		btRigidBody* body = btRigidBody::upcast(obj);
		std::cout << "Object: " << (const char*)body->getUserPointer() << ", position:";
		body->activate(true);
		btTransform trans;
		if (body && body->getMotionState())
		{
			body->getMotionState()->getWorldTransform(trans);
		}
		else
		{
			trans = obj->getWorldTransform();
		}
		std::cout << trans.getOrigin().getX() << " " << trans.getOrigin().getY() << " " << trans.getOrigin().getZ() << std::endl;
		btVector3 min, max;
		body->getAabb(min, max);
		std::cout << "Min " << min.getX() << " " << min.getY() << " " << min.getZ() << std::endl;
		std::cout << "Max " << max.getX() << " " << max.getY() << " " << max.getZ() << std::endl;
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glUseProgram(m_shaderDesc);

	//m_ball->RenderScene(nEye);
	//m_paddle2->RenderScene(nEye);
	m_paddle1->RenderScene(nEye);
	m_floor->RenderScene(nEye);
	for (auto& ball : m_balls) {
		ball->RenderScene(nEye);
	}

	glUseProgram(0);
}

void MainStage::HandleInput()
{
}

bool MainStage::checkCollisions()
{

	/* Browse all collision pairs */
	int numManifolds = m_dynamics_world->getDispatcher()->getNumManifolds();
	for (int i = 0; i < numManifolds; i++)
	{
		btPersistentManifold* contactManifold = m_dynamics_world->getDispatcher()->getManifoldByIndexInternal(i);
		const btCollisionObject* obA = contactManifold->getBody0();
		const btCollisionObject* obB = contactManifold->getBody1();

		if (std::string((const char*)obA->getUserPointer()) == std::string("Ball")
			&& std::string((const char*)obB->getUserPointer()) == std::string("Ball")) {
			std::cout << "Collisiion between " << (const char*)obA->getUserPointer() << " and " << (const char*)obB->getUserPointer() << std::endl;
		}

		/* Check all contacts points */
		int numContacts = contactManifold->getNumContacts();
		for (int j = 0; j < numContacts; j++)
		{
			btManifoldPoint& pt = contactManifold->getContactPoint(j);
			if (pt.getDistance() < 0.f)
			{
				std::cout << "Collisiion between " << (const char*)obA->getUserPointer() << " and " << (const char*)obB->getUserPointer() << std::endl;
				return true;
			}
		}
	}

	return false;
}