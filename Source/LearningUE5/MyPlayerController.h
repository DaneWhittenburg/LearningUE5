// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputAction.h" // This is required as we define an input action in UE5 that is linked to code back here
#include "InputMappingContext.h" // Every Input Actionr requires a mapping sequence to control which button it's linked to
#include "test_actor.h" // This is required as we link our controller to pull information from the actor
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
	void StartDragActor();
	void EndDragActor();

protected:
	// The mapping context to be added to the local player subsystem
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enahnced Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	// The input action for the left mouse button
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enahnced Input")
	TObjectPtr<UInputAction> IA_LeftClick;

	AActor* ActorInfo = nullptr;
};
