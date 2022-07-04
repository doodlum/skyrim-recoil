#pragma once

namespace Events
{
	void Register();
}

class hitEventHandler : public RE::BSTEventSink<RE::TESHitEvent>
{
public:
	virtual RE::BSEventNotifyControl ProcessEvent(const RE::TESHitEvent* a_event, RE::BSTEventSource<RE::TESHitEvent>* a_eventSource);

	static bool Register()
	{
		static hitEventHandler singleton;
		auto                        ScriptEventSource = RE::ScriptEventSourceHolder::GetSingleton();

		if (!ScriptEventSource) {
			logger::error("Script event source not found");
			return false;
		}

		ScriptEventSource->AddEventSink(&singleton);

		logger::info("Registered {}", typeid(singleton).name());

		return true;
	}


};
