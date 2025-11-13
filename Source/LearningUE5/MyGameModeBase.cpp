// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"

/*This is a constructor, which is always called before other functions such as begin 
play and should generally be used for system-wide definitions of feature capabilities
such as component interactions.*/

/*Note, although the units of UE5 are in cm, this project will interpret them as km since the scale of
the moon and earth is massive, so this simulation is 1E6 scaled down model*/
AMyGameModeBase::AMyGameModeBase()
{
	// PlayerControllerClass = AMyPlayerController::StaticClass();
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(
		TEXT("/Game/BP_PlayerControllers/BP_MyPlayerController"));
	
	if (PlayerControllerBPClass.Succeeded())
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
		// UE_LOG(LogTemp, Log, TEXT("3: Applied BP PlayerController"));
	}
	else
	{
		PlayerControllerClass = AMyPlayerController::StaticClass();
		// UE_LOG(LogTemp, Log, TEXT("3: Applied C++ PlayerController"));
	}
}

void AMyGameModeBase::BeginPlay()
{
	// Always call the parent class's version first
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("Calling GameModeBase BeginPlay"));

	// UE_LOG(LogTemo, Warning, TEXT("GameMode BeginPlay: Spawning PlanetActor. "));
	// Defining the inital conditions for the actor's spawn

	FVector MoonInitPos(360.0f, 0.0f, 0.0f); // Perigee distance scaled down by 1E6
	FRotator MoonInitRot(0.0f, 0.0f, 45.0f);
	FVector EarthInitPos(0.0f, 0.0f, 0.0f);
	FRotator EarthInitRot(0.0f, 0.0f, 45.0f);


	// Actually spawning the actor in with the inital conditions
	// UWorld* World = GetWorld(); can be used as an alternative to calling GetWorld() over and over
	Moon = GetWorld()->SpawnActor<APlanetActor>(MoonInitPos, MoonInitRot);
	Earth = GetWorld()->SpawnActor<APlanetActor>(EarthInitPos, EarthInitRot);

	// You can loop this spawning method if you choose
	// This manipulates a variable delcared in the Actor's header file
	if (Moon)
	{
		Moon->RadiusScale = 3.0f; // Scaled down radius of moon's orbit
		Moon->SpawnConditions(3.0f, 2);
	}
	if (Earth)
	{
		Earth->SpawnConditions(5.0f, 0);
	}

	/*We've thought about adding looping to better scale this process but ran into the issue
	of how to assign values to specific actors if you can't assign variable names in a loop.
	The fix to this is each actor can be passed a set of parameters on spawn, it is this set
	of parameters that you'll edit before passing to easier configure actors on a large scale*/
}

