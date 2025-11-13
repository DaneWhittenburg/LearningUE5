// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"


AMyPlayerController::AMyPlayerController()
{
	// Basic properties to be set ot true for mouse events
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	SetInputMode(FInputModeGameAndUI());

	// Constructor to manually pull IMC value
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMCAsset(
		TEXT("/Game/Actions/IMC_PlayerControls"));

	if (IMCAsset.Succeeded()) // Manually sets the IMC asset
	{
		// UE_LOG(LogTemp, Log, TEXT("1: Loading Input Mapping via C++"));
		InputMappingContext = IMCAsset.Object;
	}

	// UE_LOG(LogTemp, Log, TEXT("Verifying Mouse Interaction Functionality: %d, %d, %d"), bShowMouseCursor, bEnableClickEvents, bEnableMouseOverEvents)
}

void AMyPlayerController::BeginPlay() 
{
	Super::BeginPlay();
	// UE_LOG(LogTemp, Log, TEXT("Calling PlayerController BeginPlay"));

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
		{
			if (InputMappingContext)
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
				// UE_LOG(LogTemp, Log, TEXT("1: Applied InputMapping"));
			};
		}
	}
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (EnhancedInputComponent)
	{								   				 
		// Mesh Interactions Binded		   				 
		EnhancedInputComponent->BindAction(IA_LeftClick, ETriggerEvent::Started, this, &AMyPlayerController::StartInteract);
		EnhancedInputComponent->BindAction(IA_LeftClick, ETriggerEvent::Triggered, this, &AMyPlayerController::OnInteract);
		EnhancedInputComponent->BindAction(IA_LeftClick, ETriggerEvent::Completed, this, &AMyPlayerController::EndInteract);
		// UE_LOG(LogTemp, Log, TEXT("2: Binded Left Click Functions"));
	}
}
/*Below are the general interaction functions to be appliedto the left mouse button*/
// This starting function pulls all the information of the clicked actor
void AMyPlayerController::StartInteract()
{
	// Here contains the logic of what you'll want to happen when the player starts interacting
	UE_LOG(LogTemp, Log, TEXT("Starting Interact"));
	// Sees if something intercepts the cursor's, direction vector
	FHitResult HitResult;

	//Returns a boolean if intercepted
	bool bHitResult = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

	// Runs if interception is detected
	if (bHitResult)
	{
		// Pulls the information fo the actor that was hit
		ActorInfo = HitResult.GetActor();
		if (ActorInfo)
		{
			ActorName = ActorInfo->GetName();
			UE_LOG(LogTemp, Log, TEXT("Hit Actor: %s"), *ActorInfo->GetName());

			// Initial Reaction of Planet's getting clicked
			if (ActorName.Left(ActorName.Len() - 2) == TEXT("PlanetActor"))
			{
				APlanetActor* PlanetHit = Cast<APlanetActor>(ActorInfo);
				UE_LOG(LogTemp, Log, TEXT("Interacting with actor: %s"), *PlanetHit->GetName());
				// Pregnants the planet and spawns all timeline nodes
				if (PlanetHit->Pregnant == false)
				{
					PlanetHit->Pregnant = true;
					TArray<float> TempNodeData = PlanetHit->NodeData;

					// This uses the actor's stored node data to spawn timeline nodes at the recorded locations
					for (int i = 0; i < TempNodeData.Num() / 6; i++)
					{
						ATimelineNode* NewBaby = GetWorld()->SpawnActor<ATimelineNode>(FVector(TempNodeData[6*i], TempNodeData[6*i + 1], TempNodeData[6*i + 2]),
							FRotator(TempNodeData[6*i + 3], TempNodeData[6*i + 4], TempNodeData[6*i + 5]));
						NewBaby->actor_mesh->SetStaticMesh(PlanetHit->actor_mesh->GetStaticMesh());
						NewBaby->SpawnConditions(PlanetHit->actor_mesh->GetComponentScale().X);
						NewBaby->OpacityValue = 0.5f; // Makes the timeline nodes semi-transparent
					}
				}
				// Unpregnants the planet and destroys all timeline nodes
				else if (PlanetHit->Pregnant == true)
				{
					PlanetHit->Pregnant = false;

					// This iterates through all timeline nodes and destroys them
					for (TActorIterator<ATimelineNode> Iteration(GetWorld()); Iteration; ++Iteration)
					{
						AActor* IteratedActor = *Iteration;
						if (IteratedActor->GetName().StartsWith("TimelineNode"))
						{
							IteratedActor->Destroy();
						}
					}
				}
			}
		}
	}
}
void AMyPlayerController::OnInteract()
{
	// Here contains the logic of what you'll want to happen when the player is currently interacting
	if (ActorName.Left(ActorName.Len() - 2) == TEXT("TimelineNode"))
	{
		FVector ActorLocation = ActorInfo->GetActorLocation(); // Just to have
		GetWorld()->GetFirstPlayerController()->GetMousePosition(MouseX, MouseY);
		GetWorld()->GetFirstPlayerController()->DeprojectScreenPositionToWorld(MouseX, MouseY, WorldOrigin, WorldDirection);

		FVector XYMouseLocation = WorldOrigin - WorldDirection/WorldDirection.Z * WorldOrigin.Z + WorldDirection/WorldDirection.Z * ActorLocation.Z;
		float XY_Angle = FMath::Atan(XYMouseLocation.Y / XYMouseLocation.X);
		FVector WantedLocation = FVector(1000.0f * abs(FMath::Cos(XY_Angle)) * XYMouseLocation.X / abs(XYMouseLocation.X), 
			1000.0f * abs(FMath::Sin(XY_Angle)) * XYMouseLocation.Y / abs(XYMouseLocation.Y),
			ActorLocation.Z);


		// The direction/direction.z*origin .z part is to make sure the actor stays at the same z height as it started at
		// The direction/direction.z * actorlocation.z part is to make sure the actor moves in line with the mouse cursor

		ActorInfo->SetActorLocation(WantedLocation);
		// UE_LOG(LogTemp, Log, TEXT("Mouse Location: %s Wanted Location: %s XY_Angle: %f"),
			// *XYMouseLocation.ToString(), *WantedLocation.ToString(), FMath::RadiansToDegrees(XY_Angle));
	}
}
void AMyPlayerController::EndInteract()
{
	ActorInfo = nullptr;
}
