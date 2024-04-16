// Snake Game. Copyright Taukach K. All Rights Reserved.


#include "Framework/SG_Pawn.h"
#include "Camera/CameraComponent.h"

// Sets default values
ASG_Pawn::ASG_Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Origin = CreateDefaultSubobject<USceneComponent>("Origin");
	check(Origin);
	SetRootComponent(Origin);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	check(Camera);
	Camera->SetupAttachment(Origin);
}

void ASG_Pawn::UpdateLocation(const Snake::Dim& Dim, int32 CellSize, const FTransform& GridOrigin)
{
	const float WorldWidth = Dim.width * CellSize;
	const float WorldHeight = Dim.height * CellSize;

	const float HalfAngleRad = FMath::DegreesToRadians(Camera->FieldOfView * 0.5f);

	const float LocationZ = 0.5f * WorldWidth / FMath::Tan(HalfAngleRad);
	const FVector NewPawnLocation = GridOrigin.GetLocation() + FVector(0.5f * WorldHeight, 0.5f * WorldWidth, LocationZ);
	SetActorLocation(NewPawnLocation);
}

