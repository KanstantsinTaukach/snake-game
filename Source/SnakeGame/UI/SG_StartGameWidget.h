// Snake Game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SG_StartGameWidget.generated.h"

class UButton;
class UComboBoxString;

UCLASS()
class SNAKEGAME_API USG_StartGameWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* StartGameButton;

	UPROPERTY(meta = (BindWidget))
	UButton* CloseGameButton;

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* GameSpeedComboBox;

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* GridSizeComboBox;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld>  GameLevel;


	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OnStartGame();	

	UFUNCTION()
	void OnCloseGame();

	UFUNCTION()
	void OnSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	void SaveSettings();
};
