// Fill out your copyright notice in the Description page of Project Settings.

#include "TimelineNode.h"

// Sets default values
ATimelineNode::ATimelineNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	actor_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Actor's Mesh Component"));
	RootComponent = actor_mesh;

	// This is a default cube mesh pulled from the engine assets, should be changed later by playercontroller
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (MeshAsset.Succeeded())
	{
		actor_mesh->SetStaticMesh(MeshAsset.Object);
	}

	// This allows opacity to be manipulated, but requires a material that supports opacity which can't be set in c++ apparently
	DynMaterial = actor_mesh->CreateAndSetMaterialInstanceDynamic(0);
	if (DynMaterial)
	{
		DynMaterial->SetScalarParameterValue(FName("Opacity"), OpacityValue);
	}
}

// Called when the game starts or when spawned
void ATimelineNode::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATimelineNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATimelineNode::SpawnConditions(float MeshRadius)
{
	actor_mesh->SetWorldScale3D(FVector(MeshRadius, MeshRadius, MeshRadius));
}

