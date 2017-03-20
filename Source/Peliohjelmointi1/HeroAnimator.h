// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TwoDirectionalCharacterAnimator.h"
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

		void QuickAttack();
		void SlowAttack();
		void CigarAttack();
		void CigarAttackRelease();

		void Block();
		void BlockRelease();
		void Counter();

		

	UFUNCTION(BlueprintPure, Category = "Utility")
		FORCEINLINE bool CanStartAction() { return !(attacking || climbing || inhaling || blocking); }

	UFUNCTION(BlueprintCallable, Category = "Utility")
		void DoClimb();

	FORCEINLINE bool IsClimbing() { return climbing; }
	FORCEINLINE bool IsBlocking() { return blocking; }
	FORCEINLINE bool IsAttacking() { return attacking; }
	FORCEINLINE bool IsInhaling() { return inhaling; }
	FORCEINLINE bool IsCountering() { return countering; }

protected:
	
	UFUNCTION(BlueprintPure, Category = "Utility")
		FORCEINLINE class AHeroCharacter * GetHero() {
		return Cast<AHeroCharacter>(getCharacter());
	}

	UFUNCTION(BlueprintCallable, Category = "Notify")
		void ReleaseAxe();
	UFUNCTION(BlueprintCallable, Category = "Notify")
		void GrabAxe();

	UPROPERTY(BlueprintReadWrite, Category = "State")
		bool climbing;
	UPROPERTY(BlueprintReadWrite, Category = "State")
		bool blocking;
	UPROPERTY(BlueprintReadWrite, Category = "State")
		bool attacking;
	UPROPERTY(BlueprintReadWrite, Category = "State")
		bool inhaling;
	UPROPERTY(BlueprintReadWrite, Category = "State")
		bool countering;

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

	UPROPERTY(BlueprintReadWrite, Category = "State")
		float blockingAngle;	
};
