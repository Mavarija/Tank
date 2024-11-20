// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	// Things that happen, when any of the pawns based on BasePawn dies
	void HandleDestruction();
protected:
	// These are in protected because of BlueprintReadOnly
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyComponents")
	class UCapsuleComponent* capsuleComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyComponents")
	UStaticMeshComponent* baseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyComponents")
	UStaticMeshComponent* turretMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyComponents")
	USceneComponent* projectileSpawnPoint;

	void RotateTurret(FVector _lookAtTarget);

	void Fire();

private:
	// TSubclassOf was created because it is able to store a UClass,
	// which can be used to set BP_Projectile from the BP_Tank in blueprints.
	// Also Using SpawnActor<>(), which requires c++ type and Uclass..
	UPROPERTY(EditDefaultsOnly, Category = "MyCombat")
	TSubclassOf<class AProjectile> projectileClass;

	UPROPERTY(EditAnywhere, Category = "MyCombat")
	class UParticleSystem* deathParticles;

	UPROPERTY(EditAnywhere, Category = "MyCombat")
	class USoundBase* deathSound;
};
