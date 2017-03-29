// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TwoDirectionalCharacterAnimator.h"
#include "EnemyCharacter.h"
#include "BasicEnemyCharacter.h"
#include "BasicEnemyAnimator.generated.h"

/**
 *
 */
UCLASS(transient, Blueprintable, hideCategories = AnimInstance, BlueprintType)
class PELIOHJELMOINTI1_API UBasicEnemyAnimator : public UTwoDirectionalCharacterAnimator {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Combat")
		bool Attack();
	UFUNCTION(BlueprintImplementableEvent, Category = "Combat")
		bool Dodge();	

	UFUNCTION(BlueprintImplementableEvent, Category = "Death")
		void SliceHorizontally();
	UFUNCTION(BlueprintImplementableEvent, Category = "Death")
		void SliceVertically();

	UFUNCTION(BlueprintImplementableEvent, Category = "Combat")
		void SmokeStun();
	UFUNCTION(BlueprintImplementableEvent, Category = "Combat")
		void SmokeUnstun();	

protected:

	UFUNCTION(BlueprintPure, Category = "State", meta = (BlueprintThreadSafe = "true"))
		EEnemyState GetState();

	UFUNCTION(BlueprintCallable, Category = "State")
		void SetState(EEnemyState newState);

private:
	FORCEINLINE class ABasicEnemyCharacter * GetBasicEnemy() { return Cast<ABasicEnemyCharacter>(getCharacter()); }

};
