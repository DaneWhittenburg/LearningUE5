// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "Engine/World.h" //Requireed for the GetWorld object
#include "test_actor.h" // The actor we're gonna spawn in
#include "MyPlayerController.h" // The player controller which to assign to the gamemode

/*This is a constructor, which is always called before other functions such as begin 
play and should generally be used for system-wide definitions of feature capabilities
such as component interactions.*/
AMyGameModeBase::AMyGameModeBase()
{
	// PlayerControllerClass = AMyPlayerController::StaticClass();
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(
		TEXT("/Game/BP_PlayerControllers/BP_MyPlayerController"));
	
	if (PlayerControllerBPClass.Succeeded())
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
		UE_LOG(LogTemp, Log, TEXT("3: Applied BP PlayerController"));
	}
	else
	{
		PlayerControllerClass = AMyPlayerController::StaticClass();
		UE_LOG(LogTemp, Log, TEXT("3: Applied C++ PlayerController"));
	}
}

void AMyGameModeBase::BeginPlay()
{
	// Always call the parent class's version first
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("Calling GameModeBase BeginPlay"));

	// UE_LOG(LogTemo, Warning, TEXT("GameMode BeginPlay: Spawning test_actor. "));
	// Defining the inital conditions for the actor's spawn
	FVector InitPos(100.0f, 100.0f, 100.0f);
	FRotator InitRot(0.0f, 0.0f, 45.0f);
	FVector PosOffset(0.0f, 0.0f, 100.0f);

	// Actually spawning the actor in with the inital conditions
	// UWorld* World = GetWorld(); can be used as an alternative to calling GetWorld() over and over
	Atest_actor* Actor0 = GetWorld()->SpawnActor<Atest_actor>(InitPos, InitRot);
	Atest_actor* Actor1 = GetWorld()->SpawnActor<Atest_actor>(InitPos + 1*PosOffset, InitRot);
	Atest_actor* Actor2 = GetWorld()->SpawnActor<Atest_actor>(InitPos + 2*PosOffset, InitRot);

	// You can loop this spawning method if you choose

	// This manipulates  avariable delcared in the Actor's header file
	Actor0->MoveOption = 0;
	Actor1->MoveOption = 1;
	Actor2->MoveOption = 2;


	Actor0->Scalable = 1.0f;
	Actor1->Scalable = 1.1f;
	Actor2->Scalable = 1.2f;


	/*We've thought about adding looping to better scale this process but ran into the issue
	of how to assign values to specific actors if you can't assign variable names in a loop.
	The fix to this is each actor can be passed a set of parameters on spawn, it is this set
	of parameters that you'll edit before passing to easier configure actors on a large scale*/
}

