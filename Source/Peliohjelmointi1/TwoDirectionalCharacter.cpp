#include "Peliohjelmointi1.h"
#include "TwoDirectionalCharacter.h"


ATwoDirectionalCharacter::ATwoDirectionalCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = false; //Root motion controls this
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.0f;
	GetCharacterMovement()->GroundFriction = 3.f;

	speedChangeRate = 1.5f;
	targetDirection = true;
	currentDirection = true;
	currentSpeed = 0.f;
	currentForwardY = -1.f;

	bSprinting = false;

	PrimaryActorTick.bCanEverTick = true;
}

void ATwoDirectionalCharacter::Tick(float delta) {
	Super::Tick(delta);
	auto loc = GetActorLocation();
	loc.X = 0.f;
	SetActorLocation(loc);
}

void ATwoDirectionalCharacter::Move(float speed) {
	if (!bSprinting)
		speed *= 0.5f;
	
	float spd = speed - currentSpeed;
	float rate = GetWorld()->GetDeltaSeconds() * speedChangeRate;
	float change = FMath::Min(FMath::Abs(spd), rate);
	if (spd < 0.f)
		change *= -1.f;
	currentSpeed += change;
	currentSpeed = FMath::Clamp(currentSpeed, -1.f, 1.f);

	//UE_LOG(LogTemp, Warning, TEXT("Input %f, diff %f, change %f, current %f"), speed, spd, change, currentSpeed);
	if (currentSpeed != 0.f)
		targetDirection = currentSpeed > 0.f;

	currentForwardY = GetActorForwardVector().Y;
	currentDirection = currentForwardY < 0.f;
}

float ATwoDirectionalCharacter::GetDirection(FVector target){
	float y = GetActorLocation().Y;
	float ret = target.Y > y ? -1.f : 1.f;
	return ret;

}

float ATwoDirectionalCharacter::TakeDamage(float dmgAmount, struct FDamageEvent const & dmgEvent, AController * dmgInst, AActor * dmgCauser) {
	currentHitPoints -= dmgAmount;
	if (currentHitPoints <= 0)
		Kill();
	UE_LOG(LogTemp, Warning, TEXT("Hit for %f points of damage"), dmgAmount);
	return currentHitPoints;
}

void ATwoDirectionalCharacter::Kill_Implementation() {
	Cast<UTwoDirectionalCharacterAnimator>(GetMesh()->GetAnimInstance())->Kill();
}

