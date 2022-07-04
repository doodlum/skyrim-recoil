#pragma once

#include "HitEventHandler.h"

RE::DestructibleObjectData* GetDestructibleForm(RE::TESBoundObject* a_form)
{
	using func_t = decltype(&GetDestructibleForm);
	REL::Relocation<func_t> func{ REL::RelocationID(14055, 14152) };  // 1.5.97 1401832b0
	return func(a_form);
}


bool IsDestructible(RE::TESObjectREFR* a_form)
{
	if (a_form && GetDestructibleForm(a_form->GetBaseObject()))
		return true;
	return false;
}


bool HasVelocity(RE::TESObjectREFR* a_form)
{
	RE::NiPoint3 velocity;
	a_form->GetLinearVelocity(velocity);
	return velocity.Length();
}

RE::BSEventNotifyControl HitEventHandler::ProcessEvent(const RE::TESHitEvent* a_event, RE::BSTEventSource<RE::TESHitEvent>*)
{
	auto hitsource = RE::TESForm::LookupByID<RE::TESObjectWEAP>(a_event->source);
	if (hitsource && hitsource->IsMelee()) {
			auto target = a_event->target ? a_event->target.get() : nullptr;
			auto aggressor = a_event->cause ? a_event->cause->As<RE::Actor>() : nullptr;
			if (target && aggressor && target->GetFormType() != RE::FormType::ActorCharacter && !IsDestructible(target) && !HasVelocity(target))
				aggressor->NotifyAnimationGraph("recoilStart");
	}
	return RE::BSEventNotifyControl::kContinue;
}
