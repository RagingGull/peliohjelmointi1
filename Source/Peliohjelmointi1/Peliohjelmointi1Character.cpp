// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Peliohjelmointi1.h"
#include "Peliohjelmointi1Character.h"
#include "HeroAnimInstance.h"

APeliohjelmointi1Character::APeliohjelmointi1Character()
{
	// Set size for collision capsule
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
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->RelativeRotation = FRotator(0.f,180.f,0.f);

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false; //Root motion controls this
	//GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.0f;
	//GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	//GetCharacterMovement()->MaxWalkSpeed = 600.f;
	//GetCharacterMovement()->MaxFlySpeed = 600.f;
	
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	sprinting = false;
}

//////////////////////////////////////////////////////////////////////////
// Input

void APeliohjelmointi1Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("MoveRight", this, &APeliohjelmointi1Character::MoveRight);
	PlayerInputComponent->BindAxis("Sprint", this, &APeliohjelmointi1Character::Sprint);
}

void APeliohjelmointi1Character::Sprint(float value) {
	sprinting = value > 0.5f;
}

void APeliohjelmointi1Character::MoveRight(float value)
{
	auto mesh = GetMesh();
	if (mesh) {
		auto anim = Cast<UHeroAnimInstance>(mesh->GetAnimInstance());
		if (anim) {
			anim->UpdateSpeed(sprinting ? value : value * 0.5f);
		}
	}
}

