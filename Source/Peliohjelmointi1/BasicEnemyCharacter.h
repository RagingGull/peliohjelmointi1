// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnemyCharacter.h"
#include "BasicEnemyCharacter.generated.h"

/**
 *
 */
UCLASS()
class PELIOHJELMOINTI1_API ABasicEnemyCharacter : public AEnemyCharacter {
	GENERATED_BODY()

public:
	ABasicEnemyCharacter();

	//Combat
	virtual float TakeDamage(float dmgAmount, struct FDamageEvent const & dmgEvent, AController * dmgInst, AActor * dmgCauser) override;

	UFUNCTION(BlueprintPure, Category = "Combat")
		int GetDamage() { return damage; }

	UFUNCTION(BlueprintCallable, Category = "Combat")
		bool Attack();
	UFUNCTION(BlueprintCallable, Category = "Combat")
		bool Dodge();

	UFUNCTION(BlueprintCallable, Category = "Combat")
		void SmokeStun();
	UFUNCTION(BlueprintCallable, Category = "Combat")
		void SmokeUnstun();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Combat")
		void EnableAttackColliders(bool value, int colId);

	//Deathhh
	virtual void Kill_Implementation(TSubclassOf<UDamageType> dmgType);
	
private:
	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = "true"))
		int damage;

	FORCEINLINE class UBasicEnemyAnimator* GetEnemyAnim() {return Cast<UBasicEnemyAnimator>(GetMesh()->GetAnimInstance()); 	}


};
