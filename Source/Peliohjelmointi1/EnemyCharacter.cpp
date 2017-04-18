// Fill out your copyright notice in the Description page of Project Settings.

#include "Peliohjelmointi1.h"
#include "EnemyCharacter.h"


AEnemyCharacter::AEnemyCharacter() : Super() {
	AIEnabled = true;
	state = EEnemyState::ES_Idle;
	bSprinting = true;
}

AHeroCharacter * AEnemyCharacter::FindHero() {
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHeroCharacter::StaticClass(), FoundActors);
	if (FoundActors.Num() != 0) {
		return Cast<AHeroCharacter>(FoundActors[0]);
	}
	return nullptr;
}
