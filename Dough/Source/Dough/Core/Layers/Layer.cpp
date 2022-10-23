#include "dhpch.h"
#include "Dough/Core/Layers/Layer.h"

namespace Dough
{
	Layer::Layer(const std::string& name)
		: m_DebugName(name)
	{
	}

	Layer::~Layer()
	{
	}
}
