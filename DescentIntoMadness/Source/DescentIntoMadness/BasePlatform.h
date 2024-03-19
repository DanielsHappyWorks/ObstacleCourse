// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectable.h"
#include "BasePlatform.generated.h"

UCLASS()
class DESCENTINTOMADNESS_API ABasePlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasePlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere, Category = "Moving Platform")
	FVector PlatformVelocity = FVector(0, 0, 0);

	UPROPERTY(EditAnywhere, Category = "Moving Platform")
	float TravelLimit = 0;

	UPROPERTY(EditAnywhere, Category = "Moving Platform")
	FRotator RotationVelocity = FRotator(0, 0, 0);

	FVector StartLocation;

	UPROPERTY(EditAnywhere, Category = "Collectable")
	TSubclassOf<ACollectable> CollectableBP;
	
	UPROPERTY(EditAnywhere, Category = "Collectable")
	FTransform CollectablePos;

	UPROPERTY(EditAnywhere, Category = "Collectable")
	TArray<TSubclassOf<ACollectable>> CollectableTypes;

	UPROPERTY(EditAnywhere, Category = "Collectable")
	TArray<FTransform> Collectablepositions;

	void MovePlatform(float DeltaTime);

	void RotatePlatform(float DeltaTime);

	bool ShouldPlatformReturn() const;

	float GetDistanceTraveled() const;

};
