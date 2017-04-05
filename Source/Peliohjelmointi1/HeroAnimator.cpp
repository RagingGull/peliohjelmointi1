// Fill out your copyright notice in the Description page of Project Settings.

#include "Peliohjelmointi1.h"
#include "HeroAnimator.h"

void UHeroAnimator::NativeInitializeAnimation() {
	Super::NativeInitializeAnimation();

	climbTrigger = false;
	quickAttackTrigger = false;
	slowAttackTrigger = false;
	inhaleCigarTrigger = false;
	exhaleCigarTrigger = false;
	getHitRearTrigger = false;
	getHitFrontTrigger = false;
	stopExhaleTrigger = false;
	blockingAngle = 0.f;
}

bool UHeroAnimator::QuickAttack() { return (quickAttackTrigger = CanStartAction()); }

bool UHeroAnimator::SlowAttack() { return (slowAttackTrigger = CanStartAction()); }

bool UHeroAnimator::CigarAttack() { return (inhaleCigarTrigger = CanStartAction()); }

void UHeroAnimator::CigarAttackRelease(float time) { 
	exhaleDuration = time;
	if (IsState(EHeroState::HS_Inhale)) 
		exhaleCigarTrigger = true; 
}

void UHeroAnimator::Block() {
	auto hero = GetHero();
	if (hero && !IsState(EHeroState::HS_Block)) {
		if (CanStartAction())
			SetState(EHeroState::HS_Block);
		else {
			//Get mouse delta and change block angle accordingly. Y applied directly, x depends on hero's direction
			float x, y;
			Cast<APlayerController>(hero->Controller)->GetInputMouseDelta(x, y);

			if (x == 0.f && y == 0.f)
				return;
			//Flip sign of x if hero is pointing in the negative direction.
			float sfy = GetCurrentForwardY() < 0.f ? -1.f : 1.f;
			x *= sfy;

			float rate = GetWorld()->GetDeltaSeconds() * GetHero()->GetBlockSpeed();
			float change = ((FMath::Clamp(x, -5.f, 5.f) / 10.f) + (FMath::Clamp(y, -5.f, 5.f) / 10.f)) * rate;

			blockingAngle = FMath::Clamp(blockingAngle + change, 0.f, 100.f);
		}
	}
}

void UHeroAnimator::BlockRelease() {
	if (IsState(EHeroState::HS_Block)) {
		blockingAngle = FMath::Clamp(blockingAngle - GetHero()->GetBlockSpeed() * GetWorld()->GetDeltaSeconds(), 0.f, 100.f);
		if (blockingAngle == 0.f)
			SetState(EHeroState::HS_Idle);
	}
}

bool UHeroAnimator::Counter() {
	if (IsState(EHeroState::HS_Block) && blockingAngle < 67.f) {
		SetState(EHeroState::HS_Counter);
		return true;
	}
	return false;
}

bool UHeroAnimator::CanStartAction() {
	return GetState() == EHeroState::HS_Idle;
}

void UHeroAnimator::DoClimb() { climbTrigger = CanStartAction(); }

void UHeroAnimator::StopExhaling() {
	if (IsState(EHeroState::HS_Exhale))
		stopExhaleTrigger = true;
}

EHeroState UHeroAnimator::GetState() {
	auto hero = GetHero();
	if (hero)
		return hero->GetState();
	return EHeroState::HS_Idle;
}

bool UHeroAnimator::IsState(EHeroState state) {
	return GetState() == state;
}

void UHeroAnimator::SetState(EHeroState newState) {
	auto hero = GetHero();
	if (hero)
		hero->SetState(newState);
}

AHeroCharacter * UHeroAnimator::GetHero() {
	auto c = getCharacter();
	if (c)
		return Cast<AHeroCharacter>(c);
	return nullptr;
}

void UHeroAnimator::ReleaseAxe() {
	auto hero = GetHero();
	if (hero)
		hero->ReleaseAxe();
}

void UHeroAnimator::GrabAxe() {
	auto hero = GetHero();
	if (hero)
		hero->GrabAxe();
}