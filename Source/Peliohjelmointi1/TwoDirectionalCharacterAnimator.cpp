// Fill out your copyright notice in the Description page of Project Settings.

#include "Peliohjelmointi1.h"
#include "TwoDirectionalCharacterAnimator.h"



void UTwoDirectionalCharacterAnimator::NativeUpdateAnimation(float delta) {
	Super::NativeUpdateAnimation(delta);
	if (character) {
		//Duplicated fields with thread-safety in mind..
		currentSpeed = character->getCurrentSpeed();
		currentDirection = character->getCurrentDirection();
		targetDirection = character->getTargetDirection();
		currentForwardY = character->getCurrentForwardY();
	}
}

void UTwoDirectionalCharacterAnimator::NativeInitializeAnimation() {
	Super::NativeInitializeAnimation();
	auto pawnOwner = TryGetPawnOwner();
	if (pawnOwner)
		character = Cast<ATwoDirectionalCharacter>(pawnOwner);
}

void UTwoDirectionalCharacterAnimator::OnTurnEnd() {
	if (character) {
		//Keep the character on course..
		auto loc = character->GetActorLocation();
		auto rot = character->GetActorRotation();
		rot.Yaw = rot.Yaw < 0 ? -90.f : 90.f;
		loc.X = 0;
		character->SetActorLocationAndRotation(loc, rot);
	}
}

bool UTwoDirectionalCharacterAnimator::IsDead() {
	if (character)
		return character->IsDead();
	return false;
}

void UTwoDirectionalCharacterAnimator::SetDead(bool b) {
	if (character)
		character->SetDead(b);
}

void UTwoDirectionalCharacterAnimator::Stagger() { isStaggering = true; }

void UTwoDirectionalCharacterAnimator::OnStaggerEnd() { isStaggering = false; }

void UTwoDirectionalCharacterAnimator::BlockAttack() { attackBlockedTrigger = true; }
