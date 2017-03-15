// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "HeroAnimInstance.generated.h"

UCLASS(transient, Blueprintable, hideCategories = AnimInstance, BlueprintType)
class PELIOHJELMOINTI1_API UHeroAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
		UFUNCTION(BlueprintImplementableEvent, Category = "Inputs")
		float UpdateSpeed(float newSpeed);
	
};


