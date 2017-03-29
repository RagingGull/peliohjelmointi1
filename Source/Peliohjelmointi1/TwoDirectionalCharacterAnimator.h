// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TwoDirectionalCharacter.h"
#include "Animation/AnimInstance.h"
#include "GenericPlatformMath.h"
#include "GameFramework/DamageType.h"
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

	UFUNCTION(BlueprintPure, Category = "Character")
		FORCEINLINE class ATwoDirectionalCharacter * getCharacter() { return character; }

	UFUNCTION(BlueprintCallable, Category = "Notify")
		void OnTurnEnd();

	UFUNCTION(BlueprintPure, Category = "Movement", meta=( BlueprintThreadSafe = "true"))
		FORCEINLINE bool GetTargetDirection() const { return targetDirection; }

	UFUNCTION(BlueprintPure, Category = "Movement", meta = (BlueprintThreadSafe = "true"))
		FORCEINLINE bool GetCurrentDirection() const { return currentDirection; }

	UFUNCTION(BlueprintPure, Category = "Movement", meta = (BlueprintThreadSafe = "true"))
		FORCEINLINE float GetCurrentSpeed() const { return currentSpeed; }

	UFUNCTION(BlueprintPure, Category = "Movement", meta = (BlueprintThreadSafe = "true"))
		FORCEINLINE float GetCurrentForwardY() const { return currentForwardY; }

	UFUNCTION(BlueprintPure, Category = "Combat", meta = (BlueprintThreadSafe = "true"))
		FORCEINLINE bool IsDead() { return dead; };

	UFUNCTION(BlueprintImplementableEvent, Category = "Death")
		void Kill(TSubclassOf<UDamageType> dmgType);

		void Stagger();

	UFUNCTION(BlueprintCallable, Category = "Combat")
		void BlockAttack();

	UFUNCTION(BlueprintPure, Category = "Combat", meta = (BlueprintThreadSafe = "true"))
		FORCEINLINE bool IsStaggering() const { return isStaggering; }
	
protected:

	UPROPERTY(BlueprintReadWrite, Category = "Death")
		bool dead;

	UFUNCTION(BlueprintCallable, Category = "Combat")
		void OnStaggerEnd();

	UPROPERTY(BlueprintReadWrite, Category = "Combat")
		bool attackBlockedTrigger;

private:

		class ATwoDirectionalCharacter * character;

		bool targetDirection;
		bool currentDirection;
		float currentSpeed;
		float currentForwardY;

		bool isStaggering;
};
