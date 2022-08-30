#include "CollisionComponent.h"
#include "Engine.h"
#include <iostream>

namespace digi {
    void CollisionComponent::Initialize()
    {
        auto comp = m_owner->GetComponent<rbPhysicsComponent>();
        if (comp) {
            // if data was not set, get size from render component source rect 
            if (data.size.x == 0 && data.size.y == 0)
                {
                    auto renderComponent = m_owner->GetComponent<RendererComponent>();
                    if (renderComponent)
                    {
                        data.size = Vector2{renderComponent->GetSource().w,renderComponent->GetSource().h};
                    }
                }
            g_Physics.SetCollisionBox(comp->m_body, data, m_owner);
        }
    }

    void CollisionComponent::OnCollisionEnter(Actor* other)
    {
        std::cout << other->GetName() << std::endl;
        if (m_enterFunction) m_enterFunction(other);
    }

    void CollisionComponent::OnCollisionExit(Actor* other)
    {
        std::cout << other->GetName() << std::endl;
        if (m_exitFunction) m_exitFunction(other);
    }

    bool CollisionComponent::Write(const rapidjson::Value& value) const
    {
        return true;
    }

    bool CollisionComponent::Read(const rapidjson::Value& value)
    {
        Vector2 size;
        float density = 1;
        float friction = 1;
        float restitution = 0.3f;
        bool is_trigger = 0;

        READ_DATA(value, data.size);
        READ_DATA(value, data.density);
        READ_DATA(value, data.friction);
        READ_DATA(value, data.restitution);
        READ_DATA(value, data.is_trigger);
        return true;
    }

    void CollisionComponent::Update()
    {
    }
}

