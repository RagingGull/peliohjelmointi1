// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnemyCharacter.h"
#include "BossCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PELIOHJELMOINTI1_API ABossCharacter : public AEnemyCharacter
{
	GENERATED_BODY()

public:
	virtual float TakeDamage(float dmgAmount, struct FDamageEvent const & dmgEvent, AController * dmgInst, AActor * dmgCauser) override;

	
protected:
	UPROPERTY(BlueprintReadWrite, Category="Combat")
		bool isBlocking;

	UFUNCTION(BlueprintImplementableEvent, Category = "Combat")
		void OnBlocked();
	
	
};
