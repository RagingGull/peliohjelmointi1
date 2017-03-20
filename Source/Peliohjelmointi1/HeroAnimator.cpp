// Fill out your copyright notice in the Description page of Project Settings.

#include "Peliohjelmointi1.h"
#include "HeroAnimator.h"

void UHeroAnimator::NativeInitializeAnimation() {
	Super::NativeInitializeAnimation();

	blocking = false;
	climbing = false;
	attacking = false;
	inhaling = false;
	countering = false;
	climbTrigger = false;
	quickAttackTrigger = false;
	slowAttackTrigger = false;
	inhaleCigarTrigger = false;
	exhaleCigarTrigger = false;
	getHitRearTrigger = false;
	getHitFrontTrigger = false;

	blockingAngle = 0.f;
}

void UHeroAnimator::QuickAttack() { quickAttackTrigger = CanStartAction(); }

void UHeroAnimator::SlowAttack() { slowAttackTrigger = CanStartAction(); }

void UHeroAnimator::CigarAttack() { inhaleCigarTrigger = CanStartAction(); }

void UHeroAnimator::CigarAttackRelease() { if (inhaling) exhaleCigarTrigger = true; }

void UHeroAnimator::Block() {
	if (!blocking)
		blocking = CanStartAction();
	else {
		//Get mouse delta and change block angle accordingly. Y applied directly, x depends on hero's direction
		float x, y;
		Cast<APlayerController>(GetHero()->Controller)->GetInputMouseDelta(x, y);

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

void UHeroAnimator::BlockRelease() {
	//UE_LOG(LogTemp, Warning, TEXT("Angle %f"), blockingAngle);
	if (blocking) {
		blockingAngle = FMath::Clamp(blockingAngle - GetHero()->GetBlockSpeed() * GetWorld()->GetDeltaSeconds(), 0.f, 100.f);
		blocking = blockingAngle != 0.f;
	}
}

void UHeroAnimator::Counter() {
	countering = blocking && blockingAngle < 67.f;
}

void UHeroAnimator::DoClimb() { climbTrigger = CanStartAction(); }

void UHeroAnimator::ReleaseAxe() {
	GetHero()->ReleaseAxe();
}

void UHeroAnimator::GrabAxe() {
	GetHero()->GrabAxe();
}