// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksGameMode.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	currentHealth = maxHealth;

	// bind the call back DamageTaken() to delegate OnTakeAnyDamage and adding it to it's invocation list
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	toonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));

}

void UHealthComponent::DamageTaken(AActor* _damagedActor, float _damage, const UDamageType* _damageType, AController* _instigator, AActor* _damageCauser)
{
	if (_damage <= 0.0f) return;
	// decrement health
	currentHealth -= _damage;
	// UE_LOG(LogTemp, Warning, TEXT("Health: %f"), currentHealth);
	if (currentHealth <= 0.0f && toonTanksGameMode)
	{
		toonTanksGameMode->ActorDied(_damagedActor);
	}
}

