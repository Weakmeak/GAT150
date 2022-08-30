#include "EnemyComponent.h"
#include "Engine.h"
#include <iostream>

void EnemyComponent::Initialize()
{
    CharacterComponent::Initialize();
}

void EnemyComponent::Update()
{
    auto actor = m_owner->GetScene()->GetActorFromName("Player");
    if (actor)
    {
        digi::Vector2 direction = actor->GetTransform().position - m_owner->GetTransform().position;
        digi::Vector2 force = direction.Normalized() * speed;

        auto component = m_owner->GetComponent<digi::PhysicsComponent>();
        if (component) component->ApplyForce(force);
    }
}

void EnemyComponent::OnCollisionEnter(digi::Actor* other)
{
    if (other->GetTag() == "Player")
    {
        digi::Event eve;
        eve.name = "EVENT_DAMAGE";
        eve.data = damage;
        eve.receiver = other;
        digi::g_Events.Notify(eve);
    }
}

void EnemyComponent::OnCollisionExit(digi::Actor* other)
{
}

void EnemyComponent::OnNotify(const digi::Event& event)
{
    if (event.name == "EVENT_DAMAGE")
    {
        health -= std::get<float>(event.data);
        if (health <= 0)
        {
            m_owner->SetDestroyed();
        }
    }

}

bool EnemyComponent::Write(const rapidjson::Value& value) const
{
    return true;
}

bool EnemyComponent::Read(const rapidjson::Value& value)
{
    CharacterComponent::Read(value);

    return true;
}