// Fill out your copyright notice in the Description page of Project Settings.

#include "Peliohjelmointi1.h"
#include "Dead2DCharacterAnimator.h"

void UDead2DCharacterAnimator::PasteBoneTransforms(ATwoDirectionalCharacter * source) {
	DoPasteBoneTransforms(source);
}

void UDead2DCharacterAnimator::BroadcastOnPasted() {
	PastedEvent.Broadcast();
}


