#ifndef STATIC_Entity_H_
#define STATIC_Entity_H_

#include "entity.h"

//Basic Static Entity Type
namespace game
{
	class StaticEntity :
		public Entity
	{
	public:
		StaticEntity(const std::string name, const Resource *geometry, const Resource *material, const Resource *texture, const Resource *envmap);
		~StaticEntity();

		// Update geometry configuration
		void Update(float deltaTime);
		void Idle(float deltaTime);
		void Patrol(float deltaTime);
		void Chase(float deltaTime);
		void Attack(float deltaTime);
		void Die(float deltaTime);

		// Get/set attributes specific to asteroids
		glm::quat GetPatrolAngM(void) const;
		glm::quat GetChaseAngM(void) const;
		float GetChaseRadius(void) const;
		float GetChaseAngle(void) const;
		float GetAttackAngle(void) const;
		void SetPatrolAngM(glm::quat angm);
		void SetChaseAngM(glm::quat angm);
		void SetChaseRadius(float chase_radius);
		void SetChaseAngle(float chase_angle);
		void SetAttackAngle(float attack_angle);

	protected:
		// Angular momentum of asteroid
		glm::quat patrol_angm_;
		glm::quat chase_angm_;
		float chase_radius_;
		float chase_angle_;
		float attack_angle_;
	};
}

#endif // STATIC_Entity_H_