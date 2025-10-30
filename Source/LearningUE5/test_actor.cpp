// Fill out your copyright notice in the Description page of Project Settings.


#include "test_actor.h"
#include "UObject/ConstructorHelpers.h" // Allows
#include "Engine/Engine.h"

// Sets default values
Atest_actor::Atest_actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	actor_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Actor's Mesh Component"));

	// Pulls the MeshAsset to be assigned
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));

	if (MeshAsset.Succeeded())
	{
		actor_mesh->SetStaticMesh(MeshAsset.Object);
	}
	// Attaches the capability for the actor to hold a static mesh
	RootComponent = actor_mesh;

	// Enables interactive capability
	actor_mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	actor_mesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	// This must be true for all click-based events, except drag functions apparently
	actor_mesh->SetGenerateOverlapEvents(false);
}

// Called when the game starts or when spawned
void Atest_actor::BeginPlay()
{
	// This should be placed at the beginning of every BeginPlay() section
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("Calling Actor BeginPlay"));

	InitPos = GetActorLocation();
	InitRot = GetActorRotation();	
}

// Called every frame
void Atest_actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TickCount++;
	TotalTime += DeltaTime;
	// Here set the optino to how you want the actor to move
	// Option 0: Doesn't Move
	// Option 1: Linearly
	// Option 2: Circularly
	// Option 3: Circularly Differently

	CurPos = GetActorLocation();
	if (MoveOption == 0)
	{
		MoveOption = 0; // Doesn't Move
	}
	else if (MoveOption == 1) // Linear Movement
	{
		Direction = FVector(1.0f, 0.0f, 0.0f);
		DeltaPos = Direction * MoveSpeed * DeltaTime;
		NewPos = CurPos + DeltaPos;
		SetActorLocation(NewPos);
	}
	else if(MoveOption == 2) // Circular Movement
	{
		float Radius = 1000.0f * Scalable;

		// Calculates angle of circular movement based on time elapsed
		float Angle =  FMath::DegreesToRadians(FMath::Fmod(TotalTime, 360.0f)) * MoveSpeed;

		// X and Y coordinates of xy plane circular movement
		DeltaPos = FVector(Radius*FMath::Cos(Angle), Radius*FMath::Sin(Angle), 0);

		// Rotating to always be pointing towards center
		DeltaRot = FRotator(0.0f, FMath::RadiansToDegrees(Angle), 0.0f);

		// Applies calculated movement
		NewPos = InitPos + DeltaPos;
		NewRot = InitRot + DeltaRot;
		SetActorLocation(NewPos);
		SetActorRotation(NewRot);
	
	}
	else if (MoveOption == 3) // Alternative to calculating circular movement
	{
		float Angle = FMath::DegreesToRadians(FMath::Fmod(TotalTime, 360.0f))* 60;

		// Instead of pre-calculating circular movement, alters direction to be driven
		Direction = FVector(FMath::Cos(Angle), FMath::Sin(Angle), 0);
		DeltaPos = Direction * MoveSpeed * DeltaTime;
		NewPos = CurPos + DeltaPos;
		SetActorLocation(NewPos);

		/* Instead of moving in a circle about an initial position, this
		method should start at an inital position and the move in a circular
		motion from that point on*/
		
	}
	// Below is a much easier way
	// AddActorWorldOffset(DeltaMovement);

	// Below here is just logging
}


