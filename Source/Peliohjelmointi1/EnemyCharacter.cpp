// Fill out your copyright notice in the Description page of Project Settings.

#include "Peliohjelmointi1.h"
#include "EnemyCharacter.h"


AEnemyCharacter::AEnemyCharacter() : Super() {
	AIEnabled = true;
	state = EEnemyState::ES_Idle;
}
