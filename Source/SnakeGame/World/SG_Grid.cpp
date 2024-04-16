// Snake Game. Copyright Taukach K. All Rights Reserved.


#include "World/SG_Grid.h"
#include "Core/Grid.h"
#include "DrawDebugHelpers.h"
#include "Components/LineBatchComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogWorldGrid, All, All);

// Sets default values
ASG_Grid::ASG_Grid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASG_Grid::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASG_Grid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawGrid();

}

void ASG_Grid::SetModel(const TSharedPtr<Snake::Grid>& Grid, int32 InCellSize)
{
	if (!Grid.IsValid())
	{
		UE_LOG(LogWorldGrid, Fatal, TEXT("Grid is null, game aborted!"));
	}
	GridDim = Grid.Get()->dim();
	CellSize = InCellSize;
	WorldWidth = GridDim.width * CellSize;
	WorldHeight = GridDim.height * CellSize;
}

void ASG_Grid::DrawGrid()
{
	if (!GetWorld() || !GetWorld()->LineBatcher)
	{
		return;
	}

	for (int32 i = 0; i < GridDim.height + 1; ++i)
	{
		const FVector StartLocation = GetActorLocation() + GetActorForwardVector() * CellSize * i;
		const FVector EndLocation = StartLocation + GetActorRightVector() * WorldWidth;
		//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, -1.0f, 0, 3.0f);
		GetWorld()->LineBatcher->DrawLine(StartLocation, EndLocation, FLinearColor::Red, 0, 2.0f);
	}

	for (int32 i = 0; i < GridDim.width + 1; ++i)
	{
		const FVector StartLocation = GetActorLocation() + GetActorRightVector() * CellSize * i;
		const FVector EndLocation = StartLocation + GetActorForwardVector() * WorldHeight;
		//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, -1.0f, 0, 3.0f);
		GetWorld()->LineBatcher->DrawLine(StartLocation, EndLocation, FLinearColor::Red, 0, 2.0f);
	}
}

