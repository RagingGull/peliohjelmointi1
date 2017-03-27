// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "TwoDirectionalCharacter.h"
#include "Dead2DCharacterAnimator.generated.h"

/**
 *
 */


UCLASS()
class PELIOHJELMOINTI1_API UDead2DCharacterAnimator : public UAnimInstance {
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
		void PasteBoneTransforms(ATwoDirectionalCharacter * source);

DECLARE_EVENT(UDead2DCharacterAnimator, FPastedDelegate);
		FPastedDelegate& OnPasted() { return PastedEvent; }

	UPROPERTY(BlueprintReadWrite)
		bool canCopyPose;

protected:
	UFUNCTION(BlueprintImplementableEvent)
		void DoPasteBoneTransforms(ATwoDirectionalCharacter * source);

	UFUNCTION(BlueprintCallable)
		void BroadcastOnPasted();

private:
	FPastedDelegate PastedEvent;
};
