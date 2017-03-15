#pragma once

#include "GameFramework/Character.h"
#include "TwoDirectionalCharacterAnimator.h"

#include "TwoDirectionalCharacter.generated.h"


UCLASS(config = Game)
class PELIOHJELMOINTI1_API ATwoDirectionalCharacter : public ACharacter {
	GENERATED_BODY()

public:
	ATwoDirectionalCharacter();

	UFUNCTION(BlueprintCallable, Category = "Movement")
		void Move(float speed);

	UFUNCTION(BlueprintPure, Category = "Movement")
		float GetDirection(FVector target);

	//Getters
	UFUNCTION(BlueprintPure, Category = "Movement")
		FORCEINLINE bool getTargetDirection() { return targetDirection; }

	UFUNCTION(BlueprintPure, Category = "Movement")
		FORCEINLINE bool getCurrentDirection() { return currentDirection; }

	UFUNCTION(BlueprintPure, Category = "Movement")
		FORCEINLINE float getCurrentSpeed() { return currentSpeed; }

	UFUNCTION(BlueprintPure, Category = "Movement")
		FORCEINLINE float getCurrentForwardY() { return currentForwardY; }

	//bp properties
	UPROPERTY(BlueprintReadWrite, Category = "Movement")
		bool bSprinting;

	//public properties
	UPROPERTY(EditAnywhere, Category = "Movement")
		float speedChangeRate;

protected:
	virtual void Tick(float delta) override;

private:

	bool targetDirection;
	bool currentDirection;

	float currentSpeed;
	float currentForwardY;

};
