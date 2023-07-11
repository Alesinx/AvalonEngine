#include <Avalon.h>

namespace Avalon
{
	class AvalonEditor : public Application
	{
	public:
		AvalonEditor()
		{
		}

		~AvalonEditor() = default;
	};

	Application* CrateApplication()
	{
		return new AvalonEditor();
	}
}