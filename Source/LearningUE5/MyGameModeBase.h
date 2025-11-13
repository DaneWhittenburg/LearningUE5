// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlanetActor.h" // The actor we're gonna spawn
#include "Engine/World.h" //Requireed for the GetWorld object
#include "TimelineNode.h"
#include "MyPlayerController.h" // The player controller which to assign to the gamemode
#include "MyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class LEARNINGUE5_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AMyGameModeBase();
	APlanetActor* Earth;
	APlanetActor* Moon;

protected:
	// This is the function that will be called when the level starts
	virtual void BeginPlay() override;
};
