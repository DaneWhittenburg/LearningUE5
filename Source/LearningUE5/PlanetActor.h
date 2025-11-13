// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h" // Allows
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "PlanetActor.generated.h"

UCLASS()
class LEARNINGUE5_API APlanetActor : public AActor
{
	GENERATED_BODY()
	
public:	
	APlanetActor();
	// Sets default values for this actor's properties
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	// Creates a pointer variable to be referenced
	UStaticMeshComponent* actor_mesh;

	// Creating the property that movement can be edited
	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Movement")
	// UPROPERTY's require they smthn witha semi colon right after it for some reason
	float Scalable = 1.0f;
	float RadiusScale = 1.0f;
	bool Pregnant;
	int TickCount = 0;
	int MoveOption = 0;
	TArray<float> NodeData;


	/*Any variables that you might want other functions to have access to must
	be placed in the public space. We use this to assign movement options to our actors
	on spawn in MyGameModeBase.cpp so that we don't have to create a bunch of actors
	just to differentiate between movements*/

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	int NodeDecimation = 100; // Every second
	float MoveSpeed = 10.0f; // 100 cm/s
	float TotalTime = 0;
	FVector InitPos;
	FRotator InitRot;
	FVector CurPos;
	FRotator CurRot;
	FVector Direction;
	FVector DeltaPos;
	FRotator DeltaRot;
	FVector NewPos;
	FRotator NewRot;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;	
	void SpawnConditions(float MeshRadius, int MoveOption_0);
};
