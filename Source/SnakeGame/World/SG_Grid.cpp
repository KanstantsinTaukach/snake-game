// Snake Game. Copyright Taukach K. All Rights Reserved.


#include "World/SG_Grid.h"
#include "Core/Grid.h"
#include "DrawDebugHelpers.h"
#include "Components/LineBatchComponent.h"
#include "Components/StaticMeshComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogWorldGrid, All, All);

// Sets default values
ASG_Grid::ASG_Grid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Origin = CreateDefaultSubobject<USceneComponent>("Origin");
	check(Origin);
	SetRootComponent(Origin);

	GridMesh = CreateDefaultSubobject<UStaticMeshComponent>("GridMesh");
	check(GridMesh);
	GridMesh->SetupAttachment(Origin);
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
	//DrawGrid();

}

void ASG_Grid::SetModel(const TSharedPtr<SnakeGame::Grid>& Grid, uint32 InCellSize)
{
	if (!Grid.IsValid())
	{
		UE_LOG(LogWorldGrid, Fatal, TEXT("Grid is null, game aborted!"));
	}
	GridDim = Grid.Get()->dim();
	CellSize = InCellSize;
	WorldWidth = GridDim.width * CellSize;
	WorldHeight = GridDim.height * CellSize;

	// Scale mesh
	check(GridMesh->GetStaticMesh());
	const FBox Box = GridMesh->GetStaticMesh()->GetBoundingBox();
	const auto Size = Box.GetSize();

	check(Size.X);
	check(Size.Y);
	GridMesh->SetRelativeScale3D(FVector(WorldHeight / Size.X, WorldWidth / Size.Y, 1.0));
	GridMesh->SetRelativeLocation(0.5 * FVector(WorldHeight, WorldWidth, -Size.Z));

	// Setup material
	GridMaterial = GridMesh->CreateAndSetMaterialInstanceDynamic(0);
	if (GridMaterial)
	{
		GridMaterial->SetVectorParameterValue("Division", FVector(GridDim.height, GridDim.width, 0.0));
	}
}

void ASG_Grid::UpdateColors(const FSnakeColors& Colors)
{
	if (GridMaterial)
	{
		GridMaterial->SetVectorParameterValue("BackgroundColor", Colors.GridBackgroundColor);
		GridMaterial->SetVectorParameterValue("LineColor", Colors.GridLineColor);
		GridMaterial->SetVectorParameterValue("WallColor", Colors.GridWallColor);
	}
}

void ASG_Grid::DrawGrid()
{
	if (!GetWorld() || !GetWorld()->LineBatcher)
	{
		return;
	}

	for (uint32 i = 0; i < GridDim.height + 1; ++i)
	{
		const FVector StartLocation = GetActorLocation() + GetActorForwardVector() * CellSize * i;
		const FVector EndLocation = StartLocation + GetActorRightVector() * WorldWidth;
		//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, -1.0f, 0, 3.0f);
		GetWorld()->LineBatcher->DrawLine(StartLocation, EndLocation, FLinearColor::Red, 1, 2.0f);
	}

	for (uint32 i = 0; i < GridDim.width + 1; ++i)
	{
		const FVector StartLocation = GetActorLocation() + GetActorRightVector() * CellSize * i;
		const FVector EndLocation = StartLocation + GetActorForwardVector() * WorldHeight;
		//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, -1.0f, 0, 3.0f);
		GetWorld()->LineBatcher->DrawLine(StartLocation, EndLocation, FLinearColor::Red, 1, 2.0f);
	}
}

