// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TwoDirectionalCharacter.h"
#include "HeroState.h"
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

	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = "true"))
		float smokeDuration;

	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = "true"))
		float counterPromptDuration;

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
	
	virtual void Kill_Implementation(TSubclassOf<UDamageType> dmgType) override;

	virtual float TakeDamage(float dmgAmount, struct FDamageEvent const & dmgEvent, AController * dmgInst, AActor * dmgCauser) override;

	void GrabAxe();
	void ReleaseAxe();
	void ToggleAxePhysics();
	void ShoveAxe();

	UFUNCTION(BlueprintCallable, Category = "Combat")
		void RemoveBlockedDamager(UPrimitiveComponent* damager);

	UFUNCTION(BlueprintCallable, Category = "State")
		void SetState(EHeroState newState) { state = newState; }

	UFUNCTION(BlueprintPure, Category = "State")
		EHeroState GetState() const { return state; }

	UFUNCTION(BlueprintPure, Category = "Combat")
		float GetSmokeDuration() const { return smokeDuration; }

	UFUNCTION(BlueprintPure, Category = "Combat")
		float GetCounterPromptDuration() const { return counterPromptDuration; }

	UFUNCTION(BlueprintCallable, Category = "Movement")
		void ToggleMovementState();

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
		void OnCigarSmokeStart(float ratio);

	UPROPERTY(BlueprintReadWrite, Category="Combat")
		bool counterEnabled;

	UFUNCTION(BlueprintCallable, Category = "Combat")
		void AddBlockedDamager(UPrimitiveComponent* damager);

	UFUNCTION(BlueprintImplementableEvent, Category = "Combat")
		void OnBlockStarted();

	UFUNCTION(BlueprintImplementableEvent, Category = "Combat")
		void OnBlockEnded();

	UFUNCTION(BlueprintPure, Category = "Combat")
		bool IsBlacklisted(AActor* actor) const;

	UFUNCTION(BlueprintCallable, Category = "Combat")
		void AddToBlacklist(AActor* actor);

private:
	FVector GetAxeOffset() { return FVector(0.f, 0.f, 58.f); };
	

	FHeroAttackType currentAttackType;
	FHeroAttackType horizontalAttack;
	FHeroAttackType verticalAttack;
	FHeroAttackType smokeAttack;

	TArray<UPrimitiveComponent*> blockedDamagers;

	float timeAtCigarAttackBegin;

	EHeroState state;

	TArray<AActor*> damagerBlacklist;
};
