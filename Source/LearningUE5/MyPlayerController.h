// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputAction.h" // This is required as we define an input action in UE5 that is linked to code back here
#include "InputMappingContext.h" // Every Input Actionr requires a mapping sequence to control which button it's linked to
#include "PlanetActor.h" // This is required as we link our controller to pull information from the actor
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimelineNode.h"
#include "EngineUtils.h" // USed to iterate through the actor list
#include "MyPlayerController.generated.h"


/**
 * 
 */
UCLASS()
class LEARNINGUE5_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMyPlayerController();
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	// Interact Functions
	void StartInteract();
	void OnInteract();
	void EndInteract();

	// Mouse Projection Variables
	float MouseX;
	float MouseY;
	FVector WorldOrigin;
	FVector WorldDirection;
	FString ActorName;
	int ClickCount = 0;

protected:
	// The mapping context to be added to the local player subsystem
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	// The input action for the left mouse button
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_LeftClick;

	AActor* ActorInfo = nullptr;
	// FString ActorName;
};
