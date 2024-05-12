// Snake Game. Copyright Taukach K. All Rights Reserved.


#include "SnakeGame/Framework/SG_GameMode.h"
#include "SnakeGame/Core/Types.h"
#include "SnakeGame/Core/Grid.h"
#include "World/SG_Grid.h"
#include "World/SG_Snake.h"
#include "World/SG_WorldTypes.h"
#include "Framework/SG_Pawn.h"
#include "Engine/ExponentialHeightFog.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogMyGameMode, All, All);


void ASG_GameMode::StartPlay()
{
	Super::StartPlay();

	// Init core game
	SnakeGame::Settings GS;
	GS.gridDims = SnakeGame::Dim{ GridDims.X, GridDims.Y };
	GS.gameSpeed = GameSpeed;
	GS.snake.defaultSize = SnakeDefaultSize;
	GS.snake.startPosition = SnakeGame::Position{ GridDims.X / 2, GridDims.Y / 2 };

	Game = MakeUnique<SnakeGame::Game>(GS);
	check(Game.IsValid());

	// Init world grid
	const FTransform GridOrigin = FTransform::Identity;
	check(GetWorld());
	GridVisual = GetWorld()->SpawnActorDeferred<ASG_Grid>(GridVisualClass, GridOrigin);
	check(GridVisual);
	GridVisual->SetModel(Game->grid(), CellSize);
	GridVisual->FinishSpawning(GridOrigin);

	// Init world snake
	SnakeVisual = GetWorld()->SpawnActorDeferred<ASG_Snake>(SnakeVisualClass, GridOrigin);
	SnakeVisual->SetModel(Game->snake(), CellSize, Game->grid()->dim());
	SnakeVisual->FinishSpawning(GridOrigin);

	// Set pawn location fitting grid in viewport
	auto* PC = GetWorld()->GetFirstPlayerController();
	check(PC);

	auto* Pawn = Cast<ASG_Pawn>(PC->GetPawn());
	check(Pawn);
	check(Game->grid().IsValid());
	Pawn->UpdateLocation(Game->grid()->dim(), CellSize, GridOrigin);

	FindFog();
	
	// Update colors
	check(ColorsTable);
	const auto RowsCount = ColorsTable->GetRowNames().Num();
	check(RowsCount >= 1);
	ColorTableIndex = FMath::RandRange(0, RowsCount - 1);
	UpdateColors();

	SetupInput();
}

void ASG_GameMode::NextColor()
{
	if (ColorsTable)
	{
		ColorTableIndex = (ColorTableIndex + 1) % ColorsTable->GetRowNames().Num();
		UpdateColors();
	}	
}

void ASG_GameMode::UpdateColors()
{
	const auto RowName = ColorsTable->GetRowNames()[ColorTableIndex];
	const auto* ColorSet = ColorsTable->FindRow<FSnakeColors>(RowName, {});
	if (ColorSet)
	{
		// Update gird
		GridVisual->UpdateColors(*ColorSet);

		// Update scene ambient color via fog
		if (Fog && Fog->GetComponent())
		{
			Fog->GetComponent()-> FogInscatteringColor = ColorSet->SkyAtmosphereColor;
			Fog->MarkComponentsRenderStateDirty();
		}
	}
}

void ASG_GameMode::FindFog()
{
	TArray<AActor*> Fogs;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AExponentialHeightFog::StaticClass(), Fogs);
	if (Fogs.Num() > 0)
	{
		Fog = Cast<AExponentialHeightFog>(Fogs[0]);
	}
}


void ASG_GameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (Game.IsValid())
	{
		Game->update(DeltaSeconds, SnakeInput);
	}
}

ASG_GameMode::ASG_GameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASG_GameMode::SetupInput()
{
	if (!GetWorld())
	{
		return;
	}

	if (auto* PC = Cast<APlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		if (auto* InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			UE_LOG(LogMyGameMode, Display, TEXT("-----------------------InputSystemIsOk-----------------------"));
			//InputSystem->ClearAllMappings();
			InputSystem->AddMappingContext(InputMapping, 0);
		}

		auto* Input = Cast<UEnhancedInputComponent>(PC->InputComponent);
		check(Input);
		Input->BindAction(MoveForwardInputAction, ETriggerEvent::Triggered, this, &ASG_GameMode::OnMoveForward);
		UE_LOG(LogMyGameMode, Display, TEXT("-----------------------BindActionisOf-----------------------"));
		Input->BindAction(MoveRightInputAction, ETriggerEvent::Triggered, this, &ASG_GameMode::OnMoveRight);
	}	
}

void ASG_GameMode::OnMoveForward(const FInputActionValue& Value)
{
	UE_LOG(LogMyGameMode, Display, TEXT("-----------------------MoveForwardisOk-----------------------"));
	const FVector2D InputValue = Value.Get<FVector2D>();
	if (InputValue.X == 0.0)
	{
		UE_LOG(LogMyGameMode, Display, TEXT("-----------------------NOInput-----------------------"));
		return;
	}
	UE_LOG(LogMyGameMode, Display, TEXT("-----------------------ForwardInput-----------------------"));
	SnakeInput = SnakeGame::Input{ 0, static_cast<int8>(InputValue.X) };
}

void ASG_GameMode::OnMoveRight(const FInputActionValue& Value)
{
	const FVector2D InputValue = Value.Get<FVector2D>();
	if (InputValue.X == 0.0)
	{
		return;
	}
	SnakeInput = SnakeGame::Input{ static_cast<int8>(InputValue.X), 0 };
}