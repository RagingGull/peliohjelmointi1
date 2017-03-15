// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TwoDirectionalCharacter.h"
#include "HeroAnimator.h"
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

	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		AActor * axe;

	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float climbDistance;

	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		FVector axeThrowForce;

public:
	AHeroCharacter();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	void Sprint(float value);

	UPROPERTY(BlueprintReadOnly, Category = "Animation")
		class UHeroAnimator * anim;

	UPROPERTY(BlueprintReadOnly, Category = "Character")
		class USkeletalMeshComponent * axeMesh;

private:

};
