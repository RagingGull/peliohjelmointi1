// Fill out your copyright notice in the Description page of Project Settings.

#include "Peliohjelmointi1.h"
#include "TwoDirectionalCharacterAnimator.h"
#include "GenericPlatformMath.h"





void UTwoDirectionalCharacterAnimator::NativeUpdateAnimation(float delta) {
	if (character) {
		//Duplicated fields with thread-safety in mind..
		currentSpeed = character->getCurrentSpeed();
		currentDirection = character->getCurrentDirection();
		targetDirection = character->getTargetDirection();
		currentForwardY = character->getCurrentForwardY();
	}
}

void UTwoDirectionalCharacterAnimator::NativeInitializeAnimation() {
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