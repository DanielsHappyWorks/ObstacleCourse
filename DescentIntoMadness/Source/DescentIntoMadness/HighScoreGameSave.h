// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "HighScoreGameSave.generated.h"

/**
 * 
 */
UCLASS()
class DESCENTINTOMADNESS_API UHighScoreGameSave : public USaveGame
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite, Category = "High Score")
	int HighScore;
};
