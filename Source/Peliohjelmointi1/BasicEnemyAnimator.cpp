// Fill out your copyright notice in the Description page of Project Settings.

#include "Peliohjelmointi1.h"
#include "BasicEnemyAnimator.h"

EEnemyState UBasicEnemyAnimator::GetState() {
	auto enemy = GetBasicEnemy();
	if (enemy)
		return enemy->state;
	return EEnemyState::ES_Idle;
}

void UBasicEnemyAnimator::SetState(EEnemyState newState) {
	auto enemy = GetBasicEnemy();
	if (enemy)
		enemy->state = newState;
}



