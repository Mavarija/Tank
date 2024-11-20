// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
	
public:
	// Sets default values for this pawn's properties
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	APlayerController* GetTankPlayerController() const { return tankPlayerController; }

	bool bAlive = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "MyComponents")
	class USpringArmComponent* springArmComp;
	UPROPERTY(VisibleAnywhere, Category = "MyComponents")
	class UCameraComponent* cameraComp;

	UPROPERTY(EditAnywhere, Category = "MyMovement")
	float speed{};
	UPROPERTY(EditAnywhere, Category = "MyMovement")
	float turnRate{};

	void Move(float _value);
	void Turn(float _value);

	APlayerController* tankPlayerController;

};
