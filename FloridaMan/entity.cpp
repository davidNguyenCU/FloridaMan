#include "entity.h"
#include "game.h"
#include "utilities.h"
#include <iostream>
namespace game
{
Entity::Entity(const std::string name, const Resource *geometry, const Resource *material, const Resource *texture, const Resource *envmap)
    : SceneNode(name, geometry, material, texture, envmap)
{
    death_particles_ = ParticleNode(name + std::string("death"));
    death_part_ = false;
    state_ = game::State::Idle;
    forward_ = glm::vec3(0.0, 0.0, 1.0);
    up_ = glm::vec3(0.0, 1.0, 0.0);
    max_idle_timer_ = 10.0f;
    idle_timer_ = max_idle_timer_;
    max_hp_ = 50.0f;
    hp_ = max_hp_;

    max_attack_timer_ = 1.0f;
    attack_timer_ = max_attack_timer_;
}

Entity::~Entity()
{
}

void Entity::Update(float deltaTime)
{
    SceneNode *nodeHit;
    if (game_->GetPlayer()->CheckCollision(this, &nodeHit))
    {
        game_->GetPlayer()->SetCollisionEntity(this, nodeHit);
    }
    switch (state_)
    {
        case (State::Die):
            Translate(glm::vec3(0, -12, 0) * deltaTime);
            if (position_.y <= -scale_.y / 2.0f)
            {
                setDestroyFlag(true);
                game_->AlienFreed();
            }
            break;
    }
}
void Entity::TakeDamage(float amount)
{
    hp_ -= amount;
    if (hp_ <= 0.0f)
    {
        if (death_part_ && state_ != State::Die)
        {
            death_particles_.SetScale(glm::vec3(1));
            death_particles_.SetPosition(GetPosition());
            death_particles_.Start();
            game_->AddNode(&death_particles_);
        }
        state_ = State::Die;
    }
}

//Getters + Setters
State Entity::GetState(void)
{
    return state_;
}
SceneNode *Entity::GetTarget(void)
{
    return target_;
}
glm::vec3 Entity::GetForward(void)
{
    return utilities::RotateVecByQuat(forward_, orientation_);
}
glm::vec3 Entity::GetUp(void)
{
    return utilities::RotateVecByQuat(up_, orientation_);
}
void Entity::SetState(State state)
{
    state_ = state;
}
void Entity::SetTarget(SceneNode *target)
{
    target_ = target;
}
void Entity::SetEndScale(glm::vec3 end_scale)
{
    end_scale_ = end_scale;
}
bool Entity::IsAlive(void)
{
    return hp_ > 0;
}
void Entity::SetDeathEffect(ParticleNode part)
{
    death_particles_ = part;
    death_part_ = true;
}
} // namespace game
