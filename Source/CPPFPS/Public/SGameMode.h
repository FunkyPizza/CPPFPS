// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SGameMode.generated.h"


UCLASS()
class CPPFPS_API ASGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	FTimerHandle TimerHandle_BotSpawner;
	FTimerHandle TimerHandle_NextWaveStart;

	//Bots to spawn in current wave
	int32 NrOfBotsToSpawn;

	//Temp wave counter
	int32 WaveCount;

	UPROPERTY(EditDefaultsOnly, Category = "GameMode")
	float TimeBetweenWaves;
	
protected:

	//Hook BP to spawn a single bot
	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
	void SpawnNewBot();

	void SpawnBotTimerElapse();

	//Start spawning bots
	void Startwave();

	//Stop spawning bots
	void EndWave();

	//Set timer for next StartWave()
	void PrepareForNextWave();

	void CheckWaveState();


public:

	ASGameMode();


	virtual void StartPlay() override;


	virtual void Tick(float DeltaSeconds) override;
	
	
};
