// Snake Game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SnakeGame/Core/Game.h"
#include "Engine/DataTable.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "SG_GameMode.generated.h"

class ASG_Grid;
class AExponentialHeightFog;
class ASG_Snake;
class UInputAction;

UCLASS()
class SNAKEGAME_API ASG_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void StartPlay() override;
	virtual void Tick(float DeltaSeconds) override;

protected:
	ASG_GameMode();
	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "10", ClampMax = "100"), Category = "Settings")
	FIntPoint GridDims{ 10, 10 };

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "10", ClampMax = "100"), Category = "Settings")
	int32 CellSize{ 10 };

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "4", ClampMax = "10"), Category = "Settings")
	int32 SnakeDefaultSize{ 5 };

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0.1", ClampMax = "10"), Category = "Settings")
	float GameSpeed{ 1.0f };

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASG_Grid> GridVisualClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASG_Snake> SnakeVisualClass;

	UPROPERTY(EditDefaultsOnly, Category = "Design")
	UDataTable* ColorsTable;
	//TObjectPtr<UDataTable> ColorsTable;
		
	UPROPERTY(EditDefaultsOnly, Category = "SnakeInput")
	UInputAction* MoveForwardInputAction;
	//TObjectPtr<UInputAction> MoveForwardInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "SnakeInput")
	UInputAction* MoveRightInputAction;
	//TObjectPtr<UInputAction> MoveRightInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "SnakeInput")
	UInputAction* ResetGameInputAction;
	//TObjectPtr<UInputAction> ResetGameInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "SnakeInput")
	UInputMappingContext* InputMapping;
	//TObjectPtr<UInputMappingContext> InputMapping;

private:
	UPROPERTY()
	ASG_Grid* GridVisual;

	UPROPERTY()
	ASG_Snake* SnakeVisual;

	UFUNCTION(Exec, Category = "Console command")
	void NextColor();

	UPROPERTY()
	AExponentialHeightFog* Fog;

private:
	TUniquePtr<SnakeGame::Game> Game;
	int32 ColorTableIndex{ 0 };
	SnakeGame::Input SnakeInput{ 1, 0 };
	
	SnakeGame::Settings MakeSettings() const;

	/**
	* Updates Grid and ExponentialFog colours
	* according to the ColorsTable property
	*/
	void UpdateColors();

	void FindFog();

	void SetupInput();
	void OnMoveForward(const FInputActionValue& Value);
	void OnMoveRight(const FInputActionValue& Value);
	void OnGameReset(const FInputActionValue& Value);
};
