// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/DamageType.h"
#include "HeroAttackType.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FHeroAttackType {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadonly, Category= "Damage")
		TSubclassOf<UDamageType> damageType;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Damage")
		int damage;
	
	FHeroAttackType() {
		damage = 0;
	}
	FHeroAttackType(int damage, TSubclassOf<UDamageType> damageType) {
		this->damage = damage;
		this->damageType = damageType;
	}

};
