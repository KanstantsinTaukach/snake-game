// Snake Game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "SnakeGame/Core/Types.h"
#include "SG_GameUserSettings.generated.h"


UENUM()
enum class EGameSpeed : int8
{
	Worm = 0,
	Snake,
	Python
};

UENUM()
enum class EGridSize : int8
{
	Size_30x10 = 0,
	Size_40x15,
	Size_50x20,
	Size_60x25,
	Size_70x30
};

UCLASS()
class SNAKEGAME_API USG_GameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:
	USG_GameUserSettings();

	static USG_GameUserSettings* Get();

	TArray<FString> GameSpeedOptions() const { return OptionNames(GameSpeeds); }
	FString CurrentGameSpeedOption() const { return CurrentSpeed.Name; }

	TArray<FString> GridSizeOptions() const { return OptionNames(GridSizes); }
	FString CurrentGridSizeOption() const {	return CurrentGridSize.Name; }

	void SaveSnakeSettings(EGameSpeed GameSpeed, EGridSize GridSize);

	EGameSpeed GameSpeedByName(const FString& Name) const { return FindOptionByNameOrDefault(GameSpeeds, Name, EGameSpeed::Snake); }
	EGridSize GridSizeByName(const FString& Name) const { return FindOptionByNameOrDefault(GridSizes, Name, EGridSize::Size_50x20); }

	float GameSpeed() const { return CurrentSpeed.Value; }
	SnakeGame::Dim GridSize() const { return CurrentGridSize.Value; }
	
private:
	struct FSpeedData 
	{
		FString Name;
		float Value;
	};
	const TMap<EGameSpeed, FSpeedData> GameSpeeds
	{
		{EGameSpeed::Worm, {"Worm", 0.3f}},
		{EGameSpeed::Snake, {"Snake", 0.1f}},
		{EGameSpeed::Python, {"Python", 0.05f}},
	};

	struct FGridData
	{
		FString Name;
		SnakeGame::Dim Value;
	};
	const TMap<EGridSize, FGridData> GridSizes
	{
		{EGridSize::Size_30x10, {"30x10", SnakeGame::Dim {30, 10}}},
		{EGridSize::Size_40x15, {"40x15", SnakeGame::Dim {40, 15}}},
		{EGridSize::Size_50x20, {"50x20", SnakeGame::Dim {50, 20}}},
		{EGridSize::Size_60x25, {"60x25", SnakeGame::Dim {60, 25}}},
		{EGridSize::Size_70x30, {"70x30", SnakeGame::Dim {70, 30}}},
	};

	FSpeedData CurrentSpeed{ GameSpeeds[EGameSpeed::Snake] };
	FGridData CurrentGridSize{ GridSizes[EGridSize::Size_50x20] };

	template<typename MapType, typename EnumType>
	EnumType FindOptionByNameOrDefault(const MapType& Map, const FString& Name, EnumType Default) const
	{
		const auto* Founded = Algo::FindByPredicate(Map, [Name](const auto& Pair) {return Pair.Value.Name.Equals(Name); });
		return Founded ? Founded->Key : Default;
	}

	template<typename MapType>
	TArray<FString> OptionNames (const MapType& Map) const
	{
		TArray<FString> Names;

		//Algo::Transform(Map, Names, [](const auto& Pair) { return Pair.Value.Name; });
		for (const auto& Pair : Map)
		{
			Names.Add(Pair.Value.Name);
		}
		return Names;
	}
};
