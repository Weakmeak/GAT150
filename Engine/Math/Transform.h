#pragma once
#include "Vector2.h"
#include "Matrix2x2.h"
#include "Matrix3x3.h"
#include "MathUtils.h"
#include "Serial/Serializable.h"

namespace digi
{
	struct Transform  : public ISerializable{
		Transform() = default;

		Vector2 position;
		float rotation = 0;
		Vector2 scale = {1,1};

		Matrix3x3 matrix;

		Transform(Vector2 pos, float rot, Vector2 scale) : position{ pos }, rotation{ rot }, scale{ scale } {};

		// Inherited via ISerializable
		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		void Update() {
			Matrix3x3 mxScale = Matrix3x3::CreateScale(scale);
			Matrix3x3 mxRot = Matrix3x3::CreateRotation(Math::DegToRad(rotation));
			Matrix3x3 mxTran = Matrix3x3::CreateTranslation(position);

			matrix = mxTran * mxRot * mxScale;
		}

		void Update(const Matrix3x3& parent) {
			Matrix3x3 mxScale = Matrix3x3::CreateScale(scale);
			Matrix3x3 mxRot = Matrix3x3::CreateRotation(Math::DegToRad(rotation));
			Matrix3x3 mxTran = Matrix3x3::CreateTranslation(position);

			matrix = mxTran * mxRot * mxScale;
			matrix = parent * matrix;
		}

		operator Matrix3x3 () const {
			Matrix3x3 mxScale = Matrix3x3::CreateScale(scale);
			Matrix3x3 mxRot = Matrix3x3::CreateRotation(Math::DegToRad(rotation));
			Matrix3x3 mxTran = Matrix3x3::CreateTranslation(position);

			return mxTran * mxRot * mxScale;
		}
	};
}