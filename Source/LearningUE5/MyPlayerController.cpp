// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"

AMyPlayerController::AMyPlayerController()
{
	// Basic properties to be set ot true for mouse events
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

	// Constructor to manually pull IMC value
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMCAsset(
		TEXT("/Game/Actions/IMC_PlayerControls"));

	if (IMCAsset.Succeeded()) // Manually sets the IMC asset
	{
		UE_LOG(LogTemp, Log, TEXT("1: Applied C++ InputMapping"));
		InputMappingContext = IMCAsset.Object;
	}

	UE_LOG(LogTemp, Log, TEXT("Verifying Mouse Interaction Functionality: %d, %d, %d"), bShowMouseCursor, bEnableClickEvents, bEnableMouseOverEvents)
}

void AMyPlayerController::BeginPlay() 
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("Calling PlayerController BeginPlay"));

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
		{
			if (InputMappingContext)
			{
				Subsystem->AddMappingContext(InputMappingContext, 1);
				UE_LOG(LogTemp, Log, TEXT("1: Applied BP InputMapping"));
			};
		}
	}
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{								   				 
		// Mesh Interactions Binded		   				 
		EnhancedInputComponent->BindAction(IA_LeftClick, ETriggerEvent::Started, this, &AMyPlayerController::StartDragActor);
		EnhancedInputComponent->BindAction(IA_LeftClick, ETriggerEvent::Completed, this, &AMyPlayerController::EndDragActor);
		UE_LOG(LogTemp, Log, TEXT("2: Binded Left Click Functions"));
	}
}
/*Below are the general interaction functions to be appliedto the left mouse button*/
// This starting function pulls all the information of the clicked actor
void AMyPlayerController::StartDragActor()
{
	UE_LOG(LogTemp, Log, TEXT("Called StartDragActor"));
	// Sees if something intercepts the cursor's, direction vector
	FHitResult HitResult;

	//Returns a boolean if intercepted
	bool bHitResult = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

	// Runs if interception is detected
	if (bHitResult)
	{
		// Pulls the information fo the actor that was hit
		AActor* ActorHit = HitResult.GetActor();

		// This is the movement Code
		if (ActorHit)
		{
			ActorInfo = ActorHit;
			FVector ActorLocation = ActorHit->GetActorLocation();

			FVector WantedLocation = FVector(0.0f, 0.0f, 0.0f);
			ActorHit->SetActorLocation(WantedLocation);
			
		}
	}

}
void AMyPlayerController::EndDragActor()
{
	ActorInfo = nullptr;
}
