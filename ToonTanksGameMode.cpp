// Fill out your copyright notice in the Description page of Project Settings.

#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksPlayerController.h"
#include "Tank.h"
#include "Tower.h"

void AToonTanksGameMode::ActorDied(AActor* _deadActor)
{
	if (_deadActor == tank)
	{
		tank->HandleDestruction();
		if (tank->GetTankPlayerController())
		{
			toonTanksPlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false);
	}
	else if (ATower* destroyedTower = Cast<ATower>(_deadActor))
	{
		destroyedTower->HandleDestruction();
		--targetTowers;
		if (targetTowers == 0)
		{
			GameOver(true);
		}
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	handeGameStart();

}

void AToonTanksGameMode::handeGameStart()
{
	// get tower count
	targetTowers = GetTargetTowerCount();

	// set variables
	tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	toonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	// disable input
	if (toonTanksPlayerController)
	{
		toonTanksPlayerController->SetPlayerEnabledState(false);
	}
	// start timer
	FTimerHandle playerEnableTimerHandle;
	FTimerDelegate playerEnableTimerDelegate = FTimerDelegate::CreateUObject(
		toonTanksPlayerController, &AToonTanksPlayerController::SetPlayerEnabledState, true);
	// set timer
	GetWorldTimerManager().SetTimer(playerEnableTimerHandle, playerEnableTimerDelegate, startDelay, false);

}

int32 AToonTanksGameMode::GetTargetTowerCount()
{
	TArray<AActor*> towers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), towers);
	return towers.Num();
}
