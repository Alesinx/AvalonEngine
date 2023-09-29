#pragma once
#include "Avalon/ECS/Components/Component.h"

namespace Avalon
{
	class InputComponent : public Component
	{
	public:
		void Update(float deltaTime) override;
		void Serialize(YAML::Emitter& out);
		void Deserialize(const YAML::Node& inputComponentNode);

	private:
		float speed = 1.0f;
	};
}
