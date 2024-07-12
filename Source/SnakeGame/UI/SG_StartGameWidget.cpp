// Snake Game. Copyright Taukach K. All Rights Reserved.


#include "UI/SG_StartGameWidget.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "Kismet/GameplayStatics.h"
#include "Framework/SG_GameUserSettings.h"

void USG_StartGameWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	auto* UserSettings = USG_GameUserSettings::Get();
	if (!UserSettings)
	{
		UE_LOG(LogTemp, Display, TEXT("--------------CAN'T GET GameUserSettings--------------"));
		return;
	}

	check(StartGameButton);
	StartGameButton->OnClicked.AddDynamic(this, &ThisClass::OnStartGame);

	check(GameSpeedComboBox);
	GameSpeedComboBox->ClearOptions();
	for (const auto& Option : UserSettings->GameSpeedOptions())
	{
		GameSpeedComboBox->AddOption(Option);
	}
	GameSpeedComboBox->SetSelectedOption(UserSettings->CurrentGameSpeedOption());
	GameSpeedComboBox->OnSelectionChanged.AddDynamic(this, &ThisClass::OnSelectionChanged);
	
	check(GridSizeComboBox);
	GridSizeComboBox->ClearOptions();
	for (const auto& Option : UserSettings->GridSizeOptions())
	{
		GridSizeComboBox->AddOption(Option);
	}
	GridSizeComboBox->SetSelectedOption(UserSettings->CurrentGridSizeOption());
	GridSizeComboBox->OnSelectionChanged.AddDynamic(this, &ThisClass::OnSelectionChanged);
}
void USG_StartGameWidget::OnStartGame()
{
	if (!GameLevel.IsNull())
	{
		UGameplayStatics::OpenLevel(GetWorld(), FName(GameLevel.GetAssetName()));
	}
}

void USG_StartGameWidget::OnSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (SelectionType == ESelectInfo::OnMouseClick)
	{
		SaveSettings();
	}
}

void USG_StartGameWidget::SaveSettings()
{
	if (auto* UserSettings = USG_GameUserSettings::Get())
	{
		const EGameSpeed GameSpeed = UserSettings->GameSpeedByName(GameSpeedComboBox->GetSelectedOption());
		const EGridSize GridSize = UserSettings->GridSizeByName(GridSizeComboBox->GetSelectedOption());
		UserSettings->SaveSnakeSettings(GameSpeed, GridSize);
	}
}
