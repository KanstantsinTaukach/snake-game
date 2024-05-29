// Snake Game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeGame/Core/Food.h"
#include "SG_Food.generated.h"

class UStaticMeshComponent;
class UNiagaraSystem;

UCLASS()
class SNAKEGAME_API ASG_Food : public AActor
{
	GENERATED_BODY()
	
public:
	ASG_Food();

	/**
	* Set core model to be observed by the Food world actor
	* @param Food model object
	* @param CellSize world size of the cell
	* @param Dims dimensions of the grid
	*/
	void SetModel(const TSharedPtr <SnakeGame::Food>& InFood, int32 InCellSize, const SnakeGame::Dim& InDims);

	void UpdateColor(const FLinearColor& Color);

	void Explode();

protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Origin;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* FoodMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* ExplosionEffect;
	// TObjectPtr<UNiagaraSystem> ExplosionEffect;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	TWeakPtr<SnakeGame::Food> Food;
	int32 CellSize;
	SnakeGame::Dim Dims;
	FLinearColor VfxFoodColor;

	FVector GetFoodWorldLocation() const;
};
