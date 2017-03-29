// Fill out your copyright notice in the Description page of Project Settings.

#include "Peliohjelmointi1.h"
#include "HeroCharacter.h"
#include "SmokeDamage.h"
#include "HorizontalDamage.h"
#include "VerticalDamage.h"

AHeroCharacter::AHeroCharacter() : Super() {

	cigar = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cigar"));
	cigar->SetupAttachment(GetMesh(), TEXT("CigarSocket"));
	cigar->RelativeLocation = FVector::ZeroVector;

	axe = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Axe"));
	axe->SetupAttachment(GetMesh(), TEXT("AxeSocket"));
	axe->RelativeLocation = GetAxeOffset();

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

	if (axe)
		GrabAxe();

	PrimaryActorTick.bCanEverTick = true;

	horizontalAttack = FHeroAttackType(250, TSubclassOf<UDamageType>(UHorizontalDamage::StaticClass()));
	verticalAttack = FHeroAttackType(100, TSubclassOf<UDamageType>(UVerticalDamage::StaticClass()));
	smokeAttack = FHeroAttackType(0, TSubclassOf<UDamageType>(USmokeDamage::StaticClass()));
}

void AHeroCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) {
	PlayerInputComponent->BindAxis("MoveRight", this, &AHeroCharacter::Move);
	PlayerInputComponent->BindAxis("Sprint", this, &AHeroCharacter::Sprint);
	PlayerInputComponent->BindAxis("Block", this, &AHeroCharacter::Block);

	PlayerInputComponent->BindAction("QuickAttack", EInputEvent::IE_Pressed, this, &AHeroCharacter::QuickAttack);
	PlayerInputComponent->BindAction("SlowAttack", EInputEvent::IE_Pressed, this, &AHeroCharacter::SlowAttack);
	PlayerInputComponent->BindAction("CigarAttack", EInputEvent::IE_Pressed, this, &AHeroCharacter::CigarAttackStart);
	PlayerInputComponent->BindAction("CigarAttack", EInputEvent::IE_Released, this, &AHeroCharacter::CigarAttackEnd);

}

void AHeroCharacter::PostEditChangeProperty(FPropertyChangedEvent & e) {
	FName PropertyName = (e.Property != nullptr) ? e.Property->GetFName() : NAME_None;
	if (axe && PropertyName == GET_MEMBER_NAME_CHECKED(AHeroCharacter, axe)) {
		GrabAxe();
	}
	Super::PostEditChangeProperty(e);
}

void AHeroCharacter::Sprint(float value) {
	bSprinting = value > 0.5f;
}

void AHeroCharacter::Block(float value) {
	auto anim = GetAnim();
	if (anim) {
		if (value > 0.5f)
			anim->Block();
		else if (anim->IsBlocking())
			anim->BlockRelease();
	}
}

void AHeroCharacter::QuickAttack(FKey key) {
	auto anim = GetAnim();
	if (anim) {
		if (anim->IsBlocking() && counterEnabled)
			anim->Counter();
		else {
			anim->QuickAttack();
			currentAttackType = verticalAttack;
		}
	}
}

void AHeroCharacter::SlowAttack(FKey key) {
	auto anim = GetAnim();
	if (anim) {
		anim->SlowAttack();
		currentAttackType = horizontalAttack;
	}
}

void AHeroCharacter::CigarAttackStart(FKey key) {
	auto anim = GetAnim();
	if (anim) {
		anim->CigarAttack();
		currentAttackType = smokeAttack;
	}
}

void AHeroCharacter::CigarAttackEnd(FKey key) {
	auto anim = GetAnim();
	if (anim)
		anim->CigarAttackRelease();
	OnCigarSmokeStart();
}

void AHeroCharacter::GrabAxe() {
	if (GetAxe()->IsSimulatingPhysics())
		ToggleAxePhysics();
	axe->AttachToComponent(GetMesh(),
		FAttachmentTransformRules(
			EAttachmentRule::SnapToTarget,
			EAttachmentRule::SnapToTarget,
			EAttachmentRule::KeepRelative,
			true),
		"AxeSocket");
	axe->RelativeLocation = GetAxeOffset();
}

void AHeroCharacter::ReleaseAxe() {
	if (!GetAxe()->IsSimulatingPhysics())
		ToggleAxePhysics();
	axe->DetachFromComponent(FDetachmentTransformRules(
		EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, EDetachmentRule::KeepRelative, true
	));
	ShoveAxe();
}

void AHeroCharacter::ToggleAxePhysics() {
	auto mesh = GetAxe();
	if (mesh) {
		if (mesh->IsSimulatingPhysics()) {
			mesh->SetSimulatePhysics(false);
			mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		} else {
			mesh->SetSimulatePhysics(true);
			mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}
	}
}

void AHeroCharacter::ShoveAxe() {
	auto mesh = GetAxe();
	auto force = GetAxeThrowForce() * mesh->GetBodyInstance()->GetBodyMass();
	force.Y *= getCurrentForwardY();
	mesh->AddImpulse(force);
	UE_LOG(LogTemp, Warning, TEXT("Impulse of %f, %f, %f added"), force.X, force.Y, force.Z);
}

void AHeroCharacter::Tick(float delta) {
	Super::Tick(delta);
	auto anim = GetAnim();
	if (anim && ShouldClimb()) {
		anim->DoClimb();
	}
}

bool AHeroCharacter::ShouldClimb() {
	//Change to a triggerbox projecting out of hero's waist? 1 trace/tick isn't overly expensive tho..
	auto anim = GetAnim();
	if (bSprinting && anim->CanStartAction()) {
		FHitResult hit;
		FVector end = GetActorLocation();
		end.Y += getCurrentForwardY() > 0 ? climbDistance : -climbDistance;
		auto qParams = FCollisionQueryParams::DefaultQueryParam;
		qParams.bFindInitialOverlaps = false;
		qParams.MobilityType = EQueryMobilityType::Static;

		if (GetWorld()->LineTraceSingleByChannel(hit, GetActorLocation(), end, ECollisionChannel::ECC_Camera, qParams)) {
			return hit.Actor->ActorHasTag(FName(TEXT("climbable")));
		}
	}
	return false;
}

void AHeroCharacter::Kill_Implementation(TSubclassOf<UDamageType> dmgType) {
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}
