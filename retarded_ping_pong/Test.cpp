#include <bullet/btBulletCollisionCommon.h>
#include <bullet/BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>
#include <bullet/BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>

#include <memory>
#include <iostream>
#include <cstdio>
#include <chrono>
#include <thread>

static constexpr const char* obj1 = "jeden";
static constexpr const char* obj2 = "dwa";
static constexpr const char* planeName = "plane";
static constexpr const float ballSize = 2.0f;

std::chrono::system_clock::time_point a = std::chrono::system_clock::now();
std::chrono::system_clock::time_point b = std::chrono::system_clock::now();

int main2() {
	auto collisionConfig = new btDefaultCollisionConfiguration();
	auto dispatcher = new btCollisionDispatcher(collisionConfig);
	auto overlappingPairCache = new btDbvtBroadphase();
	auto solver = new btSequentialImpulseConstraintSolver();
	auto dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfig);
	auto checkCollisions = [&] {
		/* Browse all collision pairs */
		int numManifolds = dynamicsWorld->getDispatcher()->getNumManifolds();
		for (int i = 0; i < numManifolds; i++)
		{
			btPersistentManifold* contactManifold = dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
			const btCollisionObject* obA = contactManifold->getBody0();
			const btCollisionObject* obB = contactManifold->getBody1();
			if (std::string((const char*)obA->getUserPointer()) != std::string(planeName) &&
				std::string((const char*)obB->getUserPointer()) != std::string(planeName)) {
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
	};
	auto createRigidBody = [](const char* objName, float mass, float startHeight, btCollisionShape* groundShape) {

		btTransform groundTransform;
		groundTransform.setIdentity();
		groundTransform.setOrigin(btVector3(0, startHeight, 0));

		btVector3 localInertia(0, 0, 0);
		groundShape->calculateLocalInertia(mass, localInertia);
		//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo info(mass, myMotionState, groundShape, localInertia);
		// set physical properties like mass, coefficient of restitution etc
		info.m_restitution = 0.5;
		auto toRet = std::make_unique<btRigidBody>(info);
		toRet->setUserPointer((void*)(objName));
		return toRet;

	};
	auto rigidBody1 = createRigidBody(obj1, 1, 12.5, new btBoxShape(btVector3(ballSize, ballSize, ballSize)));
	auto rigidBody2 = createRigidBody(obj2, 1, 7.5, new btBoxShape(btVector3(ballSize, ballSize, ballSize)));
	auto plane = createRigidBody(planeName, 0, 0, new btStaticPlaneShape(btVector3(0.0, 1.0, 0.0), 0.0));
	dynamicsWorld->addRigidBody(rigidBody1.get());
	dynamicsWorld->addRigidBody(rigidBody2.get());
	dynamicsWorld->addRigidBody(plane.get());
	dynamicsWorld->setGravity(btVector3(0, -10, 0));

	while (true) {

		// Maintain designated frequency of 5 Hz (200 ms per frame)
		a = std::chrono::system_clock::now();
		std::chrono::duration<double, std::milli> work_time = a - b;

		if (work_time.count() < 50)
		{
			std::chrono::duration<double, std::milli> delta_ms(50 - work_time.count());
			auto delta_ms_duration = std::chrono::duration_cast<std::chrono::milliseconds>(delta_ms);
			std::this_thread::sleep_for(std::chrono::milliseconds(delta_ms_duration.count()));
		}

		b = std::chrono::system_clock::now();
		std::chrono::duration<double, std::milli> sleep_time = b - a;

		dynamicsWorld->stepSimulation(1.f / 60.0f, 10);
		int numCollisionObjects = dynamicsWorld->getNumCollisionObjects();
		//print positions of all objects
		for (int i = 0; i < numCollisionObjects; i++)
		{
			//B3_PROFILE("writeSingleInstanceTransformToCPU");
			btCollisionObject* colObj = dynamicsWorld->getCollisionObjectArray()[i];
			btRigidBody* body = btRigidBody::upcast(colObj);
			std::cout << "Object: " << (const char*)body->getUserPointer() << ", position:";
			btVector3 pos = colObj->getWorldTransform().getOrigin();
			std::cout << pos.getX() << " " << pos.getY() << " " << pos.getZ() << std::endl;

		}
		printf("Time: %f \n", (work_time + sleep_time).count());

	}
}
