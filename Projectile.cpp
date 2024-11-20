// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraShakeBase.h"
#include "Engine/World.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	projectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	RootComponent = projectileMesh;

	projectileMovComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	projectileMovComp->MaxSpeed = 1300.0f;
	projectileMovComp->InitialSpeed = 1300.0f;

	trailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SmokeTrail"));
	trailParticles->SetupAttachment(RootComponent);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	// binding the callback OnHit() to delegate OnComponentHit and adding to it's invocation list
	projectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if (launchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, launchSound, GetActorLocation());
	}
}

void AProjectile::OnHit(UPrimitiveComponent* _hitComp, AActor* _otherActor, UPrimitiveComponent* _otherComp, FVector _normalImpulse, const FHitResult& _hit)
{// make sure that the collision in the editor is set to (Query and Physics) to generate hit events
/*
	UE_LOG(LogTemp, Warning, TEXT("OnHit"));
	UE_LOG(LogTemp, Warning, TEXT("HitComp: %s"), *_hitComp->GetName());
	UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s"), *_otherActor->GetName());
	UE_LOG(LogTemp, Warning, TEXT("OtherComp: %s"), *_otherComp->GetName());
*/
	// get owner (for Apply Damage)
	AActor* myOwner = GetOwner();
	if (myOwner == nullptr)
	{
		// destroy the projectile so not to spam hit events + delete projectile on hit
		Destroy();
		return;
	}
	// get instigator controller (for Apply Damage)
	AController* myOwnerInstigator = myOwner->GetInstigatorController();
	// get damage type UClass pointer (for Apply Damage)
	UClass* damageTypeClass = UDamageType::StaticClass();
	if (_otherActor && _otherActor != this && _otherActor != myOwner)
	{
		// call ApplyDamage to generate damage event (OnTakeAnyDamage delegate will broadcast in response)
		UGameplayStatics::ApplyDamage(_otherActor, damage, myOwnerInstigator, this, damageTypeClass);
		if (hitParticles)
		{
			// spawn particles
			UGameplayStatics::SpawnEmitterAtLocation(this, hitParticles, GetActorLocation(), GetActorRotation());
		}
		if (hitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, hitSound, GetActorLocation());
		}
/*
		if (hitCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(hitCameraShakeClass);
		}
*/
	}
	// destroy outside the if statement so that we don't have any lingering projectiles
	Destroy();
}