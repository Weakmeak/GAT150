#include "Actor.h"
#include "Renderer/Renderer.h"
#include "Components/RendererComponent.h"

namespace digi {
	void Actor::Update()
	{
		for (auto& comp : m_components) {
			comp->Update();
		}
		for (auto& child : m_children) {
			child->Update();
		}
		if (m_parent) { m_trans.Update(m_parent->m_trans.matrix); }
		m_trans.Update();
	}
	void digi::Actor::Draw(Renderer ren)
	{
		//m_model.Draw(ren, m_trans.position, m_trans.rotation, m_trans.scale);
		for (auto& comp : m_components) {
			//comp->Update();
			auto renderComp = dynamic_cast<RendererComponnent*>(comp.get());
			if (renderComp) renderComp->Draw(ren);
		}
		for (auto& child : m_children) {
			child->Draw(ren);
		}
	}
	void Actor::addComponent(unique_ptr<Component> component)
	{
		component->m_owner = this;
		m_components.push_back(move(component));
	}
	void Actor::AddChild(unique_ptr<Actor> child)
	{
		child->m_parent = this;
		child->m_scene = this->m_scene;
		m_children.push_back(std::move(child));
	}
}