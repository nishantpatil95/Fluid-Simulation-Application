#include "pch.h"
#include "Event.h"

inline bool Event::IsInCategory(EventCategory category)
{
	return GetCategoryFlags() & category;
}

std::string Event::ToString() const
{
	return GetName();
}
EventDispatcher::EventDispatcher(Event& event) : m_Event(event)
{
	//LOG("%s", "EventDispatcher Contructor");
}
/*template<typename T>
bool EventDispatcher::Dispatch(EventFn<T> func)
{
	if (m_Event.GetEventType() == T::GetStaticType())
	{
		m_Event.Handled = func(*(T*)&m_Event);
		return true;
	}
	return false;
}*/
