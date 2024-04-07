// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectable.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"
#include "DescentIntoMadnessCharacter.h"

// Sets default values
ACollectable::ACollectable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->SetBoxExtent(FVector(50, 50, 50));
	CollisionBox->SetCollisionProfileName("Trigger");
	RootComponent = CollisionBox;

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ACollectable::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ACollectable::BeginPlay()
{
	Super::BeginPlay();
	CollectSound = LoadObject<USoundBase>(NULL, TEXT("/Game/Audio/SC_Collectable.SC_Collectable"));
}

// Called every frame
void ACollectable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalRotation(FRotator(0,90,0) * DeltaTime);
}

void ACollectable::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Begin"));
		if (ADescentIntoMadnessCharacter* Character = Cast<ADescentIntoMadnessCharacter>(OtherActor))
		{
			Character->Score = Character->Score + Value;
			//Play Sound
			if (CollectSound) {
				UGameplayStatics::PlaySound2D(this, CollectSound);
			}
			Destroy();
		}
	}
}

