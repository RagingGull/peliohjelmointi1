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

}

void ATwoDirectionalCharacter::Move(float speed) {
	if (!bSprinting)
		speed *= 0.5f;

	float spd = speed - currentSpeed;
	float rate = GetWorld()->GetDeltaSeconds() * speedChangeRate;
	float change = FMath::Min(FMath::Abs(spd), rate);

	if (speed < 0)
		change *= -1.f;
	currentSpeed += change;
	currentSpeed = FMath::Clamp(currentSpeed, -1.f, 1.f);

	if (currentSpeed != 0.f)
		targetDirection = currentSpeed > 0.f;

		currentForwardY = GetActorForwardVector().Y;
		currentDirection = currentForwardY < 0.f;
}

