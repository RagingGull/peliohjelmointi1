// Fill out your copyright notice in the Description page of Project Settings.

#include "Peliohjelmointi1.h"
#include "HeroCharacter.h"

AHeroCharacter::AHeroCharacter() {

	anim = Cast<UHeroAnimator>(GetMesh()->GetAnimInstance());
	axeMesh = axe->FindComponentByClass<USkeletalMeshComponent>();

	GetCapsuleComponent()->InitCapsuleSize(42.f, 80.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f, 0.f, 75.f);
	CameraBoom->RelativeRotation = FRotator(0.f, 180.f, 0.f);

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera
}

void AHeroCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) {
	PlayerInputComponent->BindAxis("MoveRight", this, &AHeroCharacter::Move);
	PlayerInputComponent->BindAxis("Sprint", this, &AHeroCharacter::Sprint);
}

void AHeroCharacter::Sprint(float value) {
	bSprinting = value > 0.5f;
}