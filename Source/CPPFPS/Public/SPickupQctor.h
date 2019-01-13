// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SPickupQctor.generated.h"

class USphereComponent;
class UDecalComponent;
class ASPowerupActor;

UCLASS()
class CPPFPS_API ASPickupQctor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPickupQctor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Componenets")
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, Category = "Componenets")
	UDecalComponent* DecalComp;

	UPROPERTY(EditInstanceOnly, Category = "Pickup Actor")
	TSubclassOf<ASPowerupActor> PowerUpClass;

	ASPowerupActor* PowerUpInstance;

	UPROPERTY(EditInstanceOnly, Category = "Pickup Actor")
	float CooldownDuration;

	FTimerHandle TimerHandle_Respawn;
	void Respawn();

public:	

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	
	
};
