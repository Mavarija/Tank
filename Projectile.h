// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class USoundBase;

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "MyCombat")
	UStaticMeshComponent* projectileMesh;
	UPROPERTY(VisibleAnywhere, Category = "MyMovement")
	class UProjectileMovementComponent* projectileMovComp;
	
	UPROPERTY(EditAnywhere)
	float damage = 50.0f;

	// Callback function to bind to OnComponentHit delegate (in BeginPlay())
	UFUNCTION()
	void OnHit(UPrimitiveComponent* _hitComp, AActor* _otherActor, UPrimitiveComponent* _otherComp, FVector _normalImpulse, const FHitResult& _hit);

	UPROPERTY(EditAnywhere, Category = "MyCombat")
	class UParticleSystem* hitParticles;

	UPROPERTY(VisibleAnywhere, Category = "MyCombat")
	class UParticleSystemComponent* trailParticles;

	UPROPERTY(EditAnywhere, Category = "MyCombat")
	USoundBase* launchSound;

	UPROPERTY(EditAnywhere, Category = "MyCombat")
	USoundBase* hitSound;
/*
	UPROPERTY(EditAnywhere, Category = "MyCombat")
	TSubclassOf<class UCameraShakeBase> hitCameraShakeClass;
*/
};
