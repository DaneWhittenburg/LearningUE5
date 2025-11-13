// Fill out your copyright notice in the Description page of Project Settings.


#include "PlanetActor.h"
#include "TimelineNode.h"

// Sets default values
APlanetActor::APlanetActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	actor_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Actor's Mesh Component"));
	RootComponent = actor_mesh;
	// Pulls the MeshAsset to be assigned
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere"));

	if (MeshAsset.Succeeded())
	{
		actor_mesh->SetStaticMesh(MeshAsset.Object);
	}
	// Enables interactive capability
	actor_mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	actor_mesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	// This must be true for all click-based events, except drag functions apparently
	actor_mesh->SetGenerateOverlapEvents(false);

	// Allows the mesh to be moved
	actor_mesh->SetMobility(EComponentMobility::Movable);
}

// Called when the game starts or when spawned
void APlanetActor::BeginPlay()
{
	// This should be placed at the beginning of every BeginPlay() section
	Super::BeginPlay();
}

// Called every frame
void APlanetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TickCount++;
	TotalTime += DeltaTime;
	// Here set the optino to how you want the actor to move
	// Option 0: Doesn't Move
	// Option 1: Linearly
	// Option 2: Circularly about a point
	// Option 3: Circularly Dfrom it's current position

	// Storing Position Every second to spawn timeline nodes
	if (TickCount % NodeDecimation == 2)
	{
		NodeData.Add(GetActorLocation().X);
		NodeData.Add(GetActorLocation().Y);
		NodeData.Add(GetActorLocation().Z);
		NodeData.Add(GetActorRotation().Pitch);
		NodeData.Add(GetActorRotation().Yaw);
		NodeData.Add(GetActorRotation().Roll);

		for (int i = 0; i < NodeData.Num(); i++)
		{
			UE_LOG(LogTemp, Log, TEXT("NodeData[%d]: %f"), i, NodeData[i]);
		}	
		UE_LOG(LogTemp, Log, TEXT(""));
	}

	CurPos = GetActorLocation();
	CurRot = GetActorRotation();
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
		float Radius = 1000.0f * RadiusScale;

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
		float Angle = FMath::DegreesToRadians(FMath::Fmod(TotalTime, 360.0f)) * 60;

		// Instead of pre-calculating circular movement, alters direction to be driven
		Direction = FVector(FMath::Cos(Angle), FMath::Sin(Angle), 0);
		DeltaPos = Direction * MoveSpeed * DeltaTime;
		NewPos = CurPos + DeltaPos;
		SetActorLocation(NewPos);

		/* Instead of moving in a circle about an initial position, this
		method should start at an inital position and the move in a circular
		motion from that point on*/
		
	}
	else if (MoveOption == 4) // Elliptical Orbit Movement mimicking the Moon-Earth Relationship assuming Earth is at the origin
	{
		UE_LOG(LogTemp, Log, TEXT(""));
	}
	
	if (Pregnant)
	{
		// Spawn TimelineNode babies here
		// UE_LOG(LogTemp, Log, TEXT("Pregnant TickCount: %int"), TickCount);
		if (TickCount % NodeDecimation == 2)
		{
			ATimelineNode* NewBaby = GetWorld()->SpawnActor<ATimelineNode>(CurPos, CurRot);
			NewBaby->actor_mesh->SetStaticMesh(actor_mesh->GetStaticMesh());
			NewBaby->SpawnConditions(actor_mesh->GetComponentScale().X);
			NewBaby->OpacityValue = 0.5f; // Makes the timeline nodes semi-transparent
		}
	}
	else
	{
		// Destroy TimelineNode babies here
		// UE_LOG(LogTemp, Log, TEXT("Not Pregnant TickCount: %int"), TickCount);
	}
	// Below is a much easier way
	// AddActorWorldOffset(DeltaMovement);
}

void APlanetActor::SpawnConditions(float MeshRadius, int MoveOption_0)
{
	actor_mesh->SetWorldScale3D(FVector(MeshRadius, MeshRadius, MeshRadius));
	this->MoveOption = MoveOption_0;
}
