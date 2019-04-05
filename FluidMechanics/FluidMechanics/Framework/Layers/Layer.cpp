#include "pch.h"
#include "Layer.h"

Layer::Layer(const std::string& debugName)
	: m_DebugName(debugName)
{
	LOG("%s", "Layer is Created")
		//LOG("%s%s", "Trace::", debugName)
}

Layer::~Layer()
{
	//LOG("%s", "Layer Destoryed")
}