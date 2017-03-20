#pragma once

#include "GameFramework/Character.h"
#include "TwoDirectionalCharacterAnimator.h"

#include "TwoDirectionalCharacter.generated.h"


UCLASS(config = Game)
class PELIOHJELMOINTI1_API ATwoDirectionalCharacter : public ACharacter {
	GENERATED_BODY()

public:
	ATwoDirectionalCharacter();	

	virtual float TakeDamage(float dmgAmount, struct FDamageEvent const & dmgEvent, AController * dmgInst, AActor * dmgCauser) override;

	UFUNCTION(BlueprintNativeEvent, Category = "Combat")
		void Kill();

	virtual void Kill_Implementation();

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

	UFUNCTION(BlueprintPure, Category = "Combat")
		FORCEINLINE float getDamage() { return damage[currentAttackType]; }

	UFUNCTION(BlueprintPure, Category = "Combat")
		FORCEINLINE float getCurrentHitpoints() { return currentHitPoints; }

	UFUNCTION(BlueprintPure, Category = "Combat")
		FORCEINLINE int getCurrentAttackType() { return currentAttackType; }

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

	int currentAttackType;

	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = "true"))
		TArray<float> damage;

	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = "true"))
		float maxHitPoints;

	float currentHitPoints;

};
