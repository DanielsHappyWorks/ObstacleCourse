// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Kismet/GameplayStatics.h"
#include "DescentIntoMadnessCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ADescentIntoMadnessCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Glide Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* GlideAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(Category = "Position", VisibleAnywhere)
	FVector CurrentPosition;

	UPROPERTY(Category = "Position", VisibleAnywhere)
	FVector PreviousPosition;

	UStaticMeshComponent* Umbrella;

	UPROPERTY(Category = "Game State", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int Score = 0;
	UPROPERTY(Category = "Game State", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int HighScore = 0;

public:
	ADescentIntoMadnessCharacter();

	void GroundMovement();

	UPROPERTY(Category = "Game State", EditAnywhere, BlueprintReadWrite)
	float Health = 1;

	UPROPERTY(Category = "Game State", EditAnywhere, BlueprintReadWrite)
	float CalculatedDamage = 0;

	UPROPERTY(Category = "Game State", EditAnywhere, BlueprintReadWrite)
	float MinDamageVelocity = 1200;

	UPROPERTY(Category = "Game State", EditAnywhere, BlueprintReadWrite)
	float MaxDamageVelocity = 2000;

	UPROPERTY(Category = "Game State", EditAnywhere, BlueprintReadWrite)
	bool IsDead = false;

	UPROPERTY(Category = "Game State", EditAnywhere, BlueprintReadWrite)
	float Durability = 1;

	UPROPERTY(Category = "Game State", EditAnywhere, BlueprintReadWrite)
	float DurabilityUsageSpeed = 0.18;

	UPROPERTY(Category = "Game State", EditAnywhere, BlueprintReadWrite)
	float DurabilityRecoverySpeed = 0.42;

	UPROPERTY(Category = "Gliding", EditAnywhere, BlueprintReadWrite)
	bool IsGliding = false;
	UPROPERTY(Category = "Gliding", EditAnywhere, BlueprintReadWrite)
	bool IsInitialGliding = false;

	UPROPERTY(EditAnywhere, Category = "Gliding")
	USoundBase* UmbrellaSound;

	UPROPERTY(Category = "Movement", EditAnywhere)
	FVector2D MovementVector = FVector2D(0, 0);
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void Glide();
	void GlideMovement();
	void StopGlide();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	virtual void Tick(float DeltaTime);

	void TakeDamage();

	void GlideTick(float DeltaTime);

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(BlueprintCallable)
	void AddScore(int ScoreToAdd);
};

