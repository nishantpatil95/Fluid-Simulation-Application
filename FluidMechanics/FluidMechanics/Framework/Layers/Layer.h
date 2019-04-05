#ifndef LAYER_H
#define LAYER_H
#include "Event.h"
#include "pch.h"

class Layer
{
public:
	Layer(const std::string& name = "Layer");
	virtual ~Layer();

	virtual void OnAttachLayer() {}
	virtual void OnDetachLayer() {}
	virtual void OnUpdateLayer() {
		LOG("On Update")
	}
	virtual void OnEventLayer(Event& event) {
		LOG("Layer::OnEventLayer called")
	}

	inline const std::string& GetName() const { return m_DebugName; }
protected:
	std::string m_DebugName;
};
#endif
