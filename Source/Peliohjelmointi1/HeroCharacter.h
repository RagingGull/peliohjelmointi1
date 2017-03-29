// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TwoDirectionalCharacter.h"
#include "HeroAnimator.h"
#include "HeroAttackType.h"
#include "Runtime/Engine/Classes/Engine/StaticMeshActor.h"
#include "GameFramework/DamageType.h"
#include "HeroCharacter.generated.h"

/**
 *
 */
UCLASS()
class PELIOHJELMOINTI1_API AHeroCharacter : public ATwoDirectionalCharacter {

	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* SideViewCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent * axe;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent * cigar;

	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float climbDistance;

	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float blockSpeed;

	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		FVector axeThrowForce;

	class UHeroAnimator * _anim;

public:
	AHeroCharacter();

	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	FORCEINLINE class UStaticMeshComponent * GetAxe() const { return axe; }
	FORCEINLINE FVector GetAxeThrowForce() const { return axeThrowForce; }

	FORCEINLINE class UStaticMeshComponent * GetCigarMesh() const { return cigar; }

	FORCEINLINE float GetClimbDistance() const { return climbDistance; }
	FORCEINLINE float GetBlockSpeed() const { return blockSpeed; }

	UFUNCTION(BlueprintPure, Category = "Combat")
		FHeroAttackType GetCurrentAttackType() const { return currentAttackType; }

	UFUNCTION(BlueprintCallable, Category = "Combat")
		void SetCurrentAttackType(FHeroAttackType type) { currentAttackType = type; }

	class UHeroAnimator * GetAnim() const { return Cast<UHeroAnimator>(GetMesh()->GetAnimInstance()); }
	
	virtual void Kill_Implementation(TSubclassOf<UDamageType> dmgType);

	void GrabAxe();
	void ReleaseAxe();
	void ToggleAxePhysics();
	void ShoveAxe();

protected:
	virtual void Tick(float delta) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent & e) override;

	void Sprint(float value);
	void Block(float value);

	void QuickAttack(FKey key);
	void SlowAttack(FKey key);
	void CigarAttackStart(FKey key);
	void CigarAttackEnd(FKey key);

	bool ShouldClimb();

	UFUNCTION(BlueprintImplementableEvent, Category="Combat")
		void OnCigarSmokeStart();

	UPROPERTY(BlueprintReadWrite, Category="Combat")
		bool counterEnabled;
	
private:
	FVector GetAxeOffset() { return FVector(0.f, 0.f, 58.f); };

	FHeroAttackType currentAttackType;
	FHeroAttackType horizontalAttack;
	FHeroAttackType verticalAttack;
	FHeroAttackType smokeAttack;

};
