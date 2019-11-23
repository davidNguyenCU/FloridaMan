#ifndef Entity_H_
#define Entity_H_

#include "scene_node.h"

namespace game
{
	enum State { Idle, Patrol, Chase, Attack, Die};

	class Game;

	//Entity Superclass
	class Entity :
		public SceneNode
	{
	public:
		Entity(const std::string name, const Resource *geometry, const Resource *material, const Resource *texture, const Resource *envmap);
		~Entity();
		
		void Update(float deltaTime);

		virtual void Idle(float deltaTime);
		virtual void Patrol(float deltaTime);
		virtual void Chase(float deltaTime);
		virtual void Attack(float deltaTime);
		virtual void Die(float deltaTime);
		virtual void TakeDamage(float amount);


		State GetState(void);
		Camera* GetTarget(void);
		glm::vec3 GetForward(void);
		glm::vec3 GetUp(void);
		void SetState(State state);
		void SetTarget(Camera* target);
		void SetGame(Game* g);

	protected:
		State state_;
		Camera* target_;
		Game* game_;
		glm::vec3 forward_;
		glm::vec3 up_;
		float hp_;

		float idle_timer_;
		float max_idle_timer_;
	};
}
#endif // Entity_H_