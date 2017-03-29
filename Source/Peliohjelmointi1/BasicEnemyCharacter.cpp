// Fill out your copyright notice in the Description page of Project Settings.

#include "Peliohjelmointi1.h"
#include "HorizontalDamage.h"
#include "VerticalDamage.h"
#include "BasicEnemyCharacter.h"
#include "BasicEnemyAnimator.h"

ABasicEnemyCharacter::ABasicEnemyCharacter() : Super(){

}

float ABasicEnemyCharacter::TakeDamage(float dmgAmount, struct FDamageEvent const & dmgEvent, AController * dmgInst, AActor * dmgCauser) {
	float ret = Super::TakeDamage(dmgAmount, dmgEvent, dmgInst, dmgCauser);
	//Ei healthii, kuolo korjaa joka osumasta :---{
	Kill(dmgEvent.DamageTypeClass);
	return ret;
}

bool ABasicEnemyCharacter::Attack() {
	auto anim = GetEnemyAnim();
	if (anim)
		return anim->Attack();
	else
		return false;
}

bool ABasicEnemyCharacter::Dodge() {
	auto anim = GetEnemyAnim();
	if (anim)
		return anim->Dodge();
	else
		return false;
}

void ABasicEnemyCharacter::SmokeStun() {
	auto anim = GetEnemyAnim();
	if (anim)
		anim->SmokeStun();
}

void ABasicEnemyCharacter::SmokeUnstun() {
	auto anim = GetEnemyAnim();
	if (anim)
		anim->SmokeUnstun();
}

void ABasicEnemyCharacter::Kill_Implementation(TSubclassOf<UDamageType> dmgType) {
	auto anim = GetEnemyAnim();
	if (anim) {
		if (dmgType->IsChildOf<UHorizontalDamage>())
			anim->SliceHorizontally();
		else if (dmgType->IsChildOf<UVerticalDamage>())
			anim->SliceVertically();
		//^ Awesome ^ | v Boring v
		else
			Super::Kill(dmgType);
	} else {
		Super::Kill(dmgType);
	}
}
