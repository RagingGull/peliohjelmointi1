#pragma once

#include "GameFramework/Character.h"
#include "GameFramework/DamageType.h"
#include "TwoDirectionalCharacterAnimator.h"

#include "TwoDirectionalCharacter.generated.h"


UCLASS(config = Game)
class PELIOHJELMOINTI1_API ATwoDirectionalCharacter : public ACharacter {
	GENERATED_BODY()

public:
	ATwoDirectionalCharacter();

	virtual float TakeDamage(float dmgAmount, struct FDamageEvent const & dmgEvent, AController * dmgInst, AActor * dmgCauser) override;

	UFUNCTION(BlueprintNativeEvent, Category = "Combat")
		void Kill(TSubclassOf<UDamageType> dmgType);

	virtual void Kill_Implementation(TSubclassOf<UDamageType> dmgType);

	UFUNCTION(BlueprintCallable, Category = "Movement")
		void Move(float speed);

	UFUNCTION(BlueprintPure, Category = "Movement")
		float GetDirection(FVector target);

	UFUNCTION(BlueprintCallable, Category = "Combat")
		void Stagger();

	UFUNCTION(BlueprintCallable, Category = "Combat")
		void BlockAttack();

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
		FORCEINLINE float getCurrentHitpoints() { return currentHitPoints; }
	UFUNCTION(BlueprintPure, Category = "Combat")
		FORCEINLINE float getHitpointRatio() { return currentHitPoints / maxHitPoints; }

	//bp properties
	UPROPERTY(BlueprintReadWrite, Category = "Movement")
		bool bSprinting;

	//public properties
	UPROPERTY(EditAnywhere, Category = "Movement")
		float speedChangeRate;

	UFUNCTION(BlueprintPure, Category = "Combat")
		FORCEINLINE bool IsDead() { return dead; };

	UFUNCTION(BlueprintCallable, Category = "Combat")
		void SetDead(bool b) { dead = b; }

protected:
	virtual void Tick(float delta) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent & e) override;
	virtual void OnConstruction(const FTransform & Transform) override;

	FORCEINLINE void SetTargetDirection(bool newDir) { targetDirection = newDir; }
private:

	bool dead;

	bool targetDirection;
	bool currentDirection;

	float currentSpeed;
	float currentForwardY;

	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = "true"))
		float maxHitPoints;

	UPROPERTY(VisibleAnywhere, Category = "Combat", meta = (AllowPrivateAccess = "true"))
		float currentHitPoints;


};
