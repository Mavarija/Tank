// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InFireRange())
	{
		// rotate turret toward the Tank
		RotateTurret(tank->GetActorLocation());
	}
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	// get player pawn, but bcz tank is a BasePawn child, we need to cast
	tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	// timer for fire rate
	GetWorldTimerManager().SetTimer(fireRateTimerHandle, this, &ATower::CheckFireCondition, fireRate, true);

}

void ATower::CheckFireCondition()
{
	if (tank == nullptr)
	{
		return;
	}
	if (InFireRange() && tank->bAlive)
	{
		Fire();
	}
}

bool ATower::InFireRange()
{
	// check if tank is valid
	if (tank)
	{
		// check to see if the Tank is in range
		float distance = FVector::Dist(GetActorLocation(), tank->GetActorLocation());
		if (distance <= fireRange)
		{
			// return true if in fire range
			return true;
		}
	}

	return false;
}
