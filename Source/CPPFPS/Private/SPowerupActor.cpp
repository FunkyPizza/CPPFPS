// Fill out your copyright notice in the Description page of Project Settings.

#include "SPowerupActor.h"
#include "Net/UnrealNetwork.h"


// Sets default values
ASPowerupActor::ASPowerupActor()
{
	PowerUpInterval = 0.0f;
	TotalNrOfTicks = 0;
	bIsPowerupActive = false;

	SetReplicates(true);
}



void ASPowerupActor::OnTickPowerup()
{
	TicksProcessed++;

	OnPowerupTicked();

	if (TicksProcessed >= TotalNrOfTicks)
	{
		OnExpired();

		bIsPowerupActive = false;
		OnRep_PowerupActive(); //OnRep function don't run on the server, this makes sure it will.

		GetWorldTimerManager().ClearTimer(TimerHandle_PowerupTick);
	}
}

void ASPowerupActor::OnRep_PowerupActive()
{
	OnPowerupStateChanged(bIsPowerupActive);
}

void ASPowerupActor::ActivatePowerup(AActor* OtherActor)
{
	OnActivated(OtherActor);

	bIsPowerupActive = true;
	OnRep_PowerupActive(); //OnRep function don't run on the server, this makes sure it will.

	if (PowerUpInterval > 0.0f)
	{

		GetWorldTimerManager().SetTimer(TimerHandle_PowerupTick, this, &ASPowerupActor::OnTickPowerup, PowerUpInterval, true);
	}
	else
	{
		OnTickPowerup();
	}
}

	void ASPowerupActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
	{
		Super::GetLifetimeReplicatedProps(OutLifetimeProps);

		DOREPLIFETIME(ASPowerupActor, bIsPowerupActive);
	}


