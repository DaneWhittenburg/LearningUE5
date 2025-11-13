// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlanetActor.h"
#include "TimelineNode.generated.h"

UCLASS()
class LEARNINGUE5_API ATimelineNode : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimelineNode();
	// Creates a pointer variable to be referenced
	UStaticMeshComponent* actor_mesh;
	UMaterialInstanceDynamic* DynMaterial;
	float OpacityValue = 0.0f;

	// Planets
	APlanetActor* Earth;
	APlanetActor* Moon;
	// Function to set spawn conditions such as scale
	void SpawnConditions(float Scalable);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
