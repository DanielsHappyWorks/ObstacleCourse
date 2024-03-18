// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlatform.h"

// Sets default values
ABasePlatform::ABasePlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABasePlatform::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
}

// Called every frame
void ABasePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void ABasePlatform::MovePlatform(float DeltaTime)
{
	// Reverse direction if we have gone too far
	if (ShouldPlatformReturn())
	{
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation += TravelLimit * MoveDirection;
		SetActorLocation(StartLocation);
		PlatformVelocity *= -1;
	}
	else
	{
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation += PlatformVelocity * DeltaTime;
		SetActorLocation(CurrentLocation);
	}
}

void ABasePlatform::RotatePlatform(float DeltaTime)
{
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}

bool ABasePlatform::ShouldPlatformReturn() const
{
	return GetDistanceTraveled() > TravelLimit;
}

float ABasePlatform::GetDistanceTraveled() const
{
	return FVector::Dist(StartLocation, GetActorLocation());
}