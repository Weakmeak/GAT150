#include "ModelComponent.h"
#include "Framework/Actor.h"
#include "Math/MathUtils.h"

namespace digi {

	void ModelComponent::Draw(Renderer& ren)
	{
		Transform trans = m_owner->GetTransform();
		m_verts.get()->Draw(ren, trans.position, Math::DegToRad(trans.rotation), trans.scale);
	}

	void ModelComponent::Update()
	{
	}
}