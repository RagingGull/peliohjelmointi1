// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TwoDirectionalCharacter.h"
#include "Animation/AnimInstance.h"
#include "GenericPlatformMath.h"
#include "TwoDirectionalCharacterAnimator.generated.h"


/**
 *
 */
UCLASS(transient, Blueprintable, hideCategories = AnimInstance, BlueprintType)
class PELIOHJELMOINTI1_API UTwoDirectionalCharacterAnimator : public UAnimInstance {
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaTimeX) override;

public:
	FORCEINLINE class ATwoDirectionalCharacter * getCharacter() { return character; }	

	UFUNCTION(BlueprintCallable, Category = "Notify")
		void OnTurnEnd();

	FORCEINLINE bool GetTargetDirection() { return targetDirection; }
	FORCEINLINE bool GetCurrentDirection() { return currentDirection; }
	FORCEINLINE float GetCurrentSpeed() { return currentSpeed; }
	FORCEINLINE float GetCurrentForwardY() { return currentForwardY; }

	FORCEINLINE bool isDead() { return killTrigger; }

	void Kill();

private:
	UPROPERTY(BlueprintReadOnly, Category="Character", meta = (AllowPrivateAccess = "true"))
	class ATwoDirectionalCharacter * character;

	UPROPERTY(BlueprintReadOnly, Category="Movement", meta = (AllowPrivateAccess = "true"))
	bool targetDirection;
	UPROPERTY(BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	bool currentDirection;
	UPROPERTY(BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float currentSpeed;
	UPROPERTY(BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float currentForwardY;

	UPROPERTY(BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	bool killTrigger;
};
