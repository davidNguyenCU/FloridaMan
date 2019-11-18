#pragma once
#include "enemy.h"
//Basic Static Enemy Type
namespace game
{
	class StaticEnemy :
		public Enemy
	{
	public:
		StaticEnemy(const std::string name, const Resource *geometry, const Resource *material);
		~StaticEnemy();

		// Update geometry configuration
		void Update(float deltaTime);
		void Patrol(float deltaTime);
		void Chase(float deltaTime);
		void Attack(float deltaTime);
		void Die(float deltaTime);

		// Get/set attributes specific to asteroids
		glm::quat GetAngM(void) const;
		float GetChaseRadius(void) const;
		float GetChaseAngle(void) const;
		float GetAttackAngle(void) const;
		void SetAngM(glm::quat angm);
		void SetChaseRadius(float chase_radius);
		void SetChaseAngle(float chase_angle);
		void SetAttackAngle(float attack_angle);

	protected:
		// Angular momentum of asteroid
		glm::quat angm_;
		float chase_radius_;
		float chase_angle_;
		float attack_angle_;
	};
}