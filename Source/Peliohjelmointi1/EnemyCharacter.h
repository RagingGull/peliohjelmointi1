// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TwoDirectionalCharacter.h"
#include "HeroCharacter.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EEnemyState : uint8 {
	ES_Idle UMETA(DisplayName="Idle"),
	ES_Attack UMETA(DisplayName="Attack"),
	ES_Cough UMETA(DisplayName = "Cough"),
	ES_Dodge UMETA(DisplayName = "Dodge"),
	ES_Shoved UMETA(DisplayName = "Shoved"),
	ES_Duck UMETA(DisplayName = "Duck"),
	ES_Dead UMETA(DisplayName = "Dead")
};

UCLASS()
class PELIOHJELMOINTI1_API AEnemyCharacter : public ATwoDirectionalCharacter
{
	GENERATED_BODY()
	
public:

	AEnemyCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "AI")
		bool AIEnabled;

	UPROPERTY(BlueprintReadWrite, Category = "State")
		EEnemyState state;

	FORCEINLINE UPrimitiveComponent * GetActiveDamager() const { return activeDamager; }

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Damage")
		UPrimitiveComponent * activeDamager;

	UFUNCTION(BlueprintCallable, Category = "Combat")
		AHeroCharacter * FindHero();
};
