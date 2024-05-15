// Snake Game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeGame/Core/Snake.h"
#include "World/SG_WorldTypes.h"
#include "SG_Snake.generated.h"

class ASG_SnakeLink;

UCLASS()
class SNAKEGAME_API ASG_Snake : public AActor
{
	GENERATED_BODY()
	
public:	
	ASG_Snake();

	void SetModel(const TSharedPtr <SnakeGame::Snake>& InSnake, int32 InCellSize, const SnakeGame::Dim& InDims);
	void UpdateColors(const FSnakeColors& Colors);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<ASG_SnakeLink> SnakeHeadClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<ASG_SnakeLink> SnakeLinkClass;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	TWeakPtr<SnakeGame::Snake> Snake;
	int32 CellSize;
	SnakeGame::Dim Dims;
	FLinearColor SnakeLinkColor;

	UPROPERTY()
	TArray<ASG_SnakeLink*> SnakeLinks;
};
