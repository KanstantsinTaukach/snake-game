// Snake Game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SG_GameOverWidget.generated.h"

class UTextBlock;
class UButton;

UCLASS()
class SNAKEGAME_API USG_GameOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetScore(int32 Score);
	void SetResetGameKeyName(const FString& ResetGameKeyName);

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScoreText;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ResetGameText;

	UPROPERTY(meta = (BindWidget))
	UButton* BackToMenuButton;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld>  MenuLevel;


	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OnBackToMenu();
};