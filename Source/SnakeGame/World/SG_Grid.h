// Snake Game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/Types.h"
#include "World/SG_WorldTypes.h"
#include "SG_Grid.generated.h"

namespace SnakeGame
{
	class Grid;
}

class UStaticMeshComponent;

UCLASS()
class SNAKEGAME_API ASG_Grid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASG_Grid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Origin;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* GridMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetModel(const TSharedPtr<SnakeGame::Grid>& Grid, uint32 InCellSize);

	void UpdateColors(const FSnakeColors& Colors);

private:
	UPROPERTY()
	UMaterialInstanceDynamic* GridMaterial;

	SnakeGame::Dim GridDim;
	uint32 CellSize;
	uint32 WorldWidth;
	uint32 WorldHeight;

	void DrawGrid();

};
