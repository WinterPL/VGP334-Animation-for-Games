#pragma once

class btRigidBody;

namespace WNTRengine::Physics
{
	class PhysicsObject
	{
	public:
		PhysicsObject() = default;
		virtual ~PhysicsObject() = default;

	protected:
		friend class PhysicsWorld;
		//this will sync the graphics with the physics
		virtual void Update() = 0;
		virtual btRigidBody* GetRigidBody() { return nullptr; }
	};

}