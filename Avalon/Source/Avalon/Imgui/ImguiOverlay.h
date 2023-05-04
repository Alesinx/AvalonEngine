#pragma once

namespace Avalon
{
	class ImguiOverlay
	{
	public:
		ImguiOverlay() {}
		virtual ~ImguiOverlay() {}

		void Initialize();
		void Update();
	private:
		float mTime = 0.f;
	};	
}

