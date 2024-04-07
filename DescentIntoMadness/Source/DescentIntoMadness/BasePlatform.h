// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectable.h"
#include "Lamp.h"
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

	UPROPERTY(EditAnywhere, Category = "Time To Live")
	bool TTLEnabled = true;

	UPROPERTY(EditAnywhere, Category = "Time To Live")
	TArray<ABasePlatform*> PreviousPlatforms;

	UPROPERTY(EditAnywhere, Category = "Time To Live")
	float TimeToLive = 100;

	UPROPERTY(EditAnywhere, Category = "Time To Live")
	float OriginalTimeToLive;

	UPROPERTY(EditAnywhere, Category = "Collectable")
	bool CollectablesEnabled = true;

	UPROPERTY(EditAnywhere, Category = "Collectable")
	TArray<TSubclassOf<ACollectable>> CollectableTypes;

	UPROPERTY(EditAnywhere, Category = "Collectable")
	TArray<FTransform> CollectablePositions;

	UPROPERTY(VisibleAnywhere, Category = "Collectable")
	TArray<ACollectable*> Collectables;

	void MovePlatform(float DeltaTime);

	void RotatePlatform(float DeltaTime);

	bool ShouldPlatformReturn() const;

	float GetDistanceTraveled() const;

	void SpawnCollectables();

	void HandleTimeToLive(float DeltaTime);

	bool IsReadyForDestruction();

	UFUNCTION(BlueprintCallable)
	float GetNormalisedTTL();

};
