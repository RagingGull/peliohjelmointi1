// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TwoDirectionalCharacter.h"
#include "Animation/AnimInstance.h"
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

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
	class ATwoDirectionalCharacter * character;

};
