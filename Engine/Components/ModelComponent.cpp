#include "ModelComponent.h"
#include "Framework/Actor.h"
#include "Math/MathUtils.h"
#include "Engine.h"

namespace digi {

	void ModelComponent::Draw(Renderer& ren)
	{
		Transform trans = m_owner->GetTransform();
		m_verts.get()->Draw(ren, trans.position, Math::DegToRad(trans.rotation), trans.scale);
	}

	void ModelComponent::Update()
	{
	}
	bool ModelComponent::Write(const rapidjson::Value& value) const
	{
		return false;
	}
	bool ModelComponent::Read(const rapidjson::Value& value)
	{
		string model_name;
		READ_DATA(value, model_name);

		m_verts = g_ResMan.Get<Model>(model_name);
		return true;
	}
}