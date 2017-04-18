// Fill out your copyright notice in the Description page of Project Settings.

#include "Peliohjelmointi1.h"
#include "BossCharacter.h"




float ABossCharacter::TakeDamage(float dmgAmount, struct FDamageEvent const & dmgEvent, AController * dmgInst, AActor * dmgCauser) {
	if (isBlocking) {
		dmgAmount = 0.f;
		OnBlocked();
	}
	return Super::TakeDamage(dmgAmount, dmgEvent, dmgInst, dmgCauser);
}