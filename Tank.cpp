// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
// #include "DrawDebugHelpers.h"

// Sets default values
ATank::ATank()
{
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	springArmComp->SetupAttachment(RootComponent);

	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	cameraComp->SetupAttachment(springArmComp);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (tankPlayerController) // check if playerControllerRef is not nullptr
	{
		// get current cursor point at location
		FHitResult hitResult;
		tankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, hitResult);
		// rotate turret to pointer location
		RotateTurret(hitResult.ImpactPoint);

		// debug sphere instead of cursor
		// DrawDebugSphere(GetWorld(), hitResult.ImpactPoint, 25.0f, 12, FColor::Blue, false, -1.0f);
	}

}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	// on death, we can't control the tank anymore, but keep the camera view
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	bAlive = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	tankPlayerController = Cast<APlayerController>(GetController()); // casting
	
}

void ATank::Move(float _value)
{
	FVector deltaLocation = FVector::ZeroVector; // same as innitializing it with (0.0f)
	// X = _value * speed * DeltaTime
	deltaLocation.X = _value * speed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(deltaLocation, true); // true = enables sweeping

}

void ATank::Turn(float _value)
{
	FRotator deltaRotation = FRotator::ZeroRotator;
	// Yaw = _value * turnRate * DeltaTime
	deltaRotation.Yaw = _value * turnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(deltaRotation, true);

}
