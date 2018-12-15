// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "STrackerBot.generated.h"

class UStaticMeshComponent;
class USHealthComponent;
class USphereComponent;
class USoundCue;

UCLASS()
class CPPFPS_API ASTrackerBot : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASTrackerBot();

protected:
	//Components
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		UStaticMeshComponent* MeshComp;
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		USHealthComponent* HealthComp;
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		USphereComponent* SphereComp;

	// Functions
	virtual void BeginPlay() override;
	FVector GetNextPathPoint();
	void SelfDestruct();
	void DamageSelf();

	UFUNCTION()
		void HandleTakeDamage(USHealthComponent* OwningHealthComp, float Health, float HealthDelta, const class UDamageType* DamageType,
			class AController* InstigatedBy, AActor* DamageCauser);


	// Tracking Modifiers
	UPROPERTY(EditDefaultsOnly, Category = "Tracker Bot")
		float MovementForce;
	UPROPERTY(EditDefaultsOnly, Category = "Tracker Bot")
		float RequiredDistanceToTarget;
	UPROPERTY(EditDefaultsOnly, Category = "Tracker Bot")
		bool bUseVelocityChange;
	UPROPERTY(EditDefaultsOnly, Category = "Tracker Bot")
		float ExplosionRadius;
	UPROPERTY(EditDefaultsOnly, Category = "Tracker Bot")
		float ExplosionDamage;
	UPROPERTY(EditDefaultsOnly, Category = "Tracker Bot")
		float SelfDamageInterval;
	UPROPERTY(EditDefaultsOnly, Category = "Tracker Bot")
		UParticleSystem* ExplosionEffect;
	UPROPERTY(EditDefaultsOnly, Category = "Tracker Bot")
		USoundCue* SelfDestructSound;
	UPROPERTY(EditDefaultsOnly, Category = "Tracker Bot")
		USoundCue* ExplosionSound;
		//Other Variables

		//Dynamic Material to pulse on damage
		UMaterialInstanceDynamic* MatInst;

	//Next point in navigation path
	FVector NextPathPoint;

	FTimerHandle TimerHandle_SelfDamage;

	bool bExploded;
	bool bStartSelfDestruction;


public:
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;



};
