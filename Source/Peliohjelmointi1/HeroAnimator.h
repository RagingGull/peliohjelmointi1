// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TwoDirectionalCharacterAnimator.h"
#include "HeroState.h"
#include "HeroCharacter.h"
#include "HeroAnimator.generated.h"

/**
 *
 */

UCLASS(transient, Blueprintable, hideCategories = AnimInstance, BlueprintType)
class PELIOHJELMOINTI1_API UHeroAnimator : public UTwoDirectionalCharacterAnimator {
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTimeX) override;

	bool QuickAttack();
	bool SlowAttack();
	bool CigarAttack();
	void CigarAttackRelease(float time);

	void Block();
	void BlockRelease();
	bool Counter();

	UFUNCTION(BlueprintPure, Category = "Utility")
		bool CanStartAction();

	UFUNCTION(BlueprintCallable, Category = "Utility")
		void DoClimb();

	UFUNCTION(BlueprintCallable, Category = "Combat")
		void StopExhaling();

protected:

	UFUNCTION(BlueprintPure, Category = "Utility")
		class AHeroCharacter * GetHero();

	UFUNCTION(BlueprintCallable, Category = "Notify")
		void ReleaseAxe();
	UFUNCTION(BlueprintCallable, Category = "Notify")
		void GrabAxe();

	UFUNCTION(BlueprintPure, Category = "IK", meta = (BlueprintThreadSafe = "true"))
		bool IsAxeHandIKActive();

	UPROPERTY(BlueprintReadWrite, Category = "Trigger")
		bool climbTrigger;
	UPROPERTY(BlueprintReadWrite, Category = "Trigger")
		bool quickAttackTrigger;
	UPROPERTY(BlueprintReadWrite, Category = "Trigger")
		bool slowAttackTrigger;
	UPROPERTY(BlueprintReadWrite, Category = "Trigger")
		bool inhaleCigarTrigger;
	UPROPERTY(BlueprintReadWrite, Category = "Trigger")
		bool exhaleCigarTrigger;
	UPROPERTY(BlueprintReadWrite, Category = "Trigger")
		bool getHitRearTrigger;
	UPROPERTY(BlueprintReadWrite, Category = "Trigger")
		bool getHitFrontTrigger;
	UPROPERTY(BlueprintReadWrite, Category = "Trigger")
		bool stopExhaleTrigger;

	UPROPERTY(BlueprintReadWrite, Category = "State")
		float blockingAngle;

	UFUNCTION(BlueprintPure, Category = "State", meta = (BlueprintThreadSafe = "true"))
		bool IsState(EHeroState state);

	UFUNCTION(BlueprintPure, Category = "State", meta = (BlueprintThreadSafe = "true"))
		EHeroState GetState();

	UFUNCTION(BlueprintCallable, Category = "State")
		void SetState(EHeroState newState);

	UPROPERTY(BlueprintReadWrite, Category = "State")
		float exhaleDuration;

	UFUNCTION(BlueprintPure, Category = "IK", meta = (BlueprintThreadSafe = "true"))
		FVector GetAxeIkLoc() const { return axeIkLoc; }

private:
	FVector axeIkLoc;

	
};
