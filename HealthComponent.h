// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	float maxHealth{ 100.0f };
	float currentHealth{};

	// Callback function to be bind to a delegate (OnTakeAnyDamage)
	UFUNCTION()
	void DamageTaken(AActor* _damagedActor, float _damage, const UDamageType* _damageType, class AController* _instigator, AActor* _damageCauser);
		
	class AToonTanksGameMode* toonTanksGameMode;

};
