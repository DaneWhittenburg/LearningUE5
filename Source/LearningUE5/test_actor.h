// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "test_actor.generated.h"

UCLASS()
class LEARNINGUE5_API Atest_actor : public AActor
{
	GENERATED_BODY()
	
public:	
	Atest_actor();
	// Sets default values for this actor's properties
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	// Creates a pointer variable to be reference in .cpp
	UStaticMeshComponent* actor_mesh;

	// Creating the property that movement can be edited
	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Movement")
	// UPROPERTY's require they smthn witha semi colon right after it for some reason
	int MoveOption = 2;
	float Scalable = 1.0f;
	bool Interacted = false;

	/*Any variables that you might want other functions to have access to must
	be placed in the public space. We use this to assign movement options to our actors
	on spawn in MyGameModeBase.cpp so that we don't have to create a bunch of actors
	just to differentiate between movements*/

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	int TickCount = 0;
	float MoveSpeed = 100.0f; // 100 cm/s
	float TotalTime = 0;
	FVector InitPos;
	FRotator InitRot;
	FVector CurPos;
	FVector Direction;
	FVector DeltaPos;
	FRotator DeltaRot;
	FVector NewPos;
	FRotator NewRot;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;	
};
