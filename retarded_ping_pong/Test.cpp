#include <bullet/btBulletCollisionCommon.h>
#include <bullet/BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>
#include <bullet/BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>

#include <memory>
#include <iostream>

static constexpr const char* obj1 = "jeden";
static constexpr const char* obj2 = "dwa";
static constexpr const char* planeName = "plane";
static constexpr const float ballSize = 2.0f;


//int main() {
//	auto collisionConfig = new btDefaultCollisionConfiguration();
//	auto dispatcher = new btCollisionDispatcher(collisionConfig);
//	auto overlappingPairCache = new btDbvtBroadphase();
//	auto solver = new btSequentialImpulseConstraintSolver();
//	auto dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfig);
//	auto checkCollisions = [&] {
//		/* Browse all collision pairs */
//		int numManifolds = dynamicsWorld->getDispatcher()->getNumManifolds();
//		for (int i = 0; i < numManifolds; i++)
//		{
//			btPersistentManifold* contactManifold = dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
//			const btCollisionObject* obA = contactManifold->getBody0();
//			const btCollisionObject* obB = contactManifold->getBody1();
//			if (std::string((const char*)obA->getUserPointer()) != std::string(planeName) &&
//				 std::string((const char*)obB->getUserPointer()) != std::string(planeName)) {
//				std::cout << "Collisiion between " << (const char*)obA->getUserPointer() << " and " << (const char*)obB->getUserPointer() << std::endl;
//			}
//
//			/* Check all contacts points */
//			int numContacts = contactManifold->getNumContacts();
//			for (int j = 0; j < numContacts; j++)
//			{
//				btManifoldPoint& pt = contactManifold->getContactPoint(j);
//				if (pt.getDistance() < 0.f)
//				{
//					std::cout << "Collisiion between " << (const char*)obA->getUserPointer() << " and " << (const char*)obB->getUserPointer() << std::endl;
//					return true;
//				}
//			}
//		}
//
//		return false;
//	};
//	auto createRigidBody = [](const char* objName, float startHeight, btCollisionShape* groundShape) {
//
//		btTransform groundTransform;
//		groundTransform.setIdentity();
//		groundTransform.setOrigin(btVector3(0, startHeight, 0));
//
//		btScalar mass(1);
//		btVector3 localInertia(0, 0, 0);
//		groundShape->calculateLocalInertia(mass, localInertia);
//		//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
//		btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
//		btRigidBody::btRigidBodyConstructionInfo info(mass, myMotionState, groundShape, localInertia);
//		// set physical properties like mass, coefficient of restitution etc
//		info.m_mass = 10;
//		info.m_restitution = 0.5;
//		auto toRet = std::make_unique<btRigidBody>(info);
//		toRet->setUserPointer((void*)(objName));
//		return toRet;
//
//	};
//	auto rigidBody1 = createRigidBody(obj1, 2.5, new btSphereShape(ballSize));
//	auto rigidBody2 = createRigidBody(obj2, 7.5, new btSphereShape(ballSize));
//	auto plane = createRigidBody(planeName, 0, new btStaticPlaneShape(btVector3(0.0, 1.0, 0.0), 0.0));
//	dynamicsWorld->addRigidBody(rigidBody1.get());
//	dynamicsWorld->addRigidBody(rigidBody2.get());
//	dynamicsWorld->addRigidBody(plane.get());
//	dynamicsWorld->setGravity(btVector3(0, -10, 0));
//
//	while (true) {
//		dynamicsWorld->stepSimulation(1.f / 10000.f,10);
//
//		checkCollisions();
//		//print positions of all objects
//		for (int j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--)
//		{
//			btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
//			btRigidBody* body = btRigidBody::upcast(obj);
//			std::cout << "Object: " << (const char*)body->getUserPointer() << ", position:";
//			body->activate(true);
//			btTransform trans;
//			if (body && body->getMotionState())
//			{
//				body->getMotionState()->getWorldTransform(trans);
//			}
//			else
//			{
//				trans = obj->getWorldTransform();
//			}
//			std::cout << trans.getOrigin().getX() << " " << trans.getOrigin().getY() << " " << trans.getOrigin().getZ() << std::endl;
//			btVector3 min, max;
//			body->getAabb(min, max);
//			std::cout << "Min " << min.getX() << " " << min.getY() << " " << min.getZ() << std::endl;
//			std::cout << "Max " << max.getX() << " " << max.getY() << " " << max.getZ() << std::endl;
//		}
//	}
//}
