// Copyright Epic Games, Inc. All Rights Reserved.

#include "DescentIntoMadnessCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ADescentIntoMadnessCharacter

ADescentIntoMadnessCharacter::ADescentIntoMadnessCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	GroundMovement();

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 600.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)


	Umbrella = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Umbrella"));
	Umbrella->SetVisibility(false);
}

void ADescentIntoMadnessCharacter::GroundMovement()
{
	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->GravityScale = 1.0f;
	GetCharacterMovement()->MaxAcceleration = 2048;
}

void ADescentIntoMadnessCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	CurrentPosition = GetActorLocation();
}

void ADescentIntoMadnessCharacter::Tick(float DeltaTime)
{
	// Call the base class  
	Super::Tick(DeltaTime);

	PreviousPosition = CurrentPosition;
	CurrentPosition = GetActorLocation();

	GlideTick(DeltaTime);

	TakeDamage();
}

void ADescentIntoMadnessCharacter::TakeDamage()
{
	if (GetCharacterMovement()->IsFalling()) {
		//Calculate damage based on velocity
		//TODO make non linear?
		float velocity = GetVelocity().Z * -1;
		if (velocity > MinDamageVelocity) {
			CalculatedDamage = velocity / MaxDamageVelocity;
		}
	} else {
		//Apply damage after falling
		Health -= CalculatedDamage;
		CalculatedDamage = 0;

		if (Health <= 0) {
			IsDead = true;
		}
	}
}

void ADescentIntoMadnessCharacter::GlideTick(float DeltaTime)
{
	//UE5 uses 0-1 for a percentage value?! Why?!
	int maxDurability = 1;
	if (bIsGliding) {
		Durability -= maxDurability * DurabilityUsageSpeed * DeltaTime;
		UE_LOG(LogTemplateCharacter, Warning, TEXT("Is Gliding"));
	}

	if (Durability <= 0) {
		StopGlide();
	}

	if (!GetCharacterMovement()->IsFalling()) {
		UE_LOG(LogTemplateCharacter, Warning, TEXT("Is Not Falling"));
		Durability = Durability <= maxDurability ? Durability + maxDurability * DurabilityRecoverySpeed * DeltaTime : maxDurability;
		StopGlide();
	}

	if (bIsGliding) {
		UE_LOG(LogTemplateCharacter, Warning, TEXT("Durability: %f, Falling Speed %f "), Durability, GetVelocity().Z);
		//decelerate the falling speed
		//If we go over the gliding speed apply a force to slow down of hald the current velocity to slow down
		if (GetVelocity().Z * -1 > GetCharacterMovement()->BrakingDecelerationFalling) {
			GetCharacterMovement()->AddImpulse(FVector(0, 0, GetVelocity().Z * -1 / 2));
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void ADescentIntoMadnessCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Gliding
		EnhancedInputComponent->BindAction(GlideAction, ETriggerEvent::Started, this, &ADescentIntoMadnessCharacter::Glide);
		EnhancedInputComponent->BindAction(GlideAction, ETriggerEvent::Completed, this, &ADescentIntoMadnessCharacter::StopGlide);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADescentIntoMadnessCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADescentIntoMadnessCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ADescentIntoMadnessCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ADescentIntoMadnessCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ADescentIntoMadnessCharacter::Glide()
{
	if (Durability <= 0) {
		UE_LOG(LogTemplateCharacter, Warning, TEXT("Out of Durability"));
		return;
	}

	if (GetCharacterMovement()->IsFalling()) {
		bIsGliding = true;
		//start gliding
		UE_LOG(LogTemplateCharacter, Warning, TEXT("Started Gliding"));
		Umbrella->SetVisibility(true);
		GlideMovement();
	}
}

void ADescentIntoMadnessCharacter::GlideMovement()
{
	GetCharacterMovement()->AirControl = 0.9f;
	GetCharacterMovement()->GravityScale = 0.1f;
	GetCharacterMovement()->MaxAcceleration = 1024;
	GetCharacterMovement()->MaxWalkSpeed = 600;
	GetCharacterMovement()->BrakingDecelerationFalling = 350.f;
}

void ADescentIntoMadnessCharacter::StopGlide()
{
	//reset gliding
	bIsGliding = false;
	Umbrella->SetVisibility(false);
	GroundMovement();
}