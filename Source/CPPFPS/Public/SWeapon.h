// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SWeapon.generated.h"


class USkeletalMeshComponent;
class UDamageType;
class UParticleSystem;

// Contains information of a single weapon linetrace
USTRUCT()
struct FHitScanTrace
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TEnumAsByte<EPhysicalSurface> SurfaceType;

	UPROPERTY()
	FVector_NetQuantize TraceTo;
};


UCLASS()
class CPPFPS_API ASWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASWeapon();

protected:
 
	//Class Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* MeshComp;

	virtual void BeginPlay() override;
	virtual void Fire();
	void PlayerFireEffects(FVector TaceEnd);

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerFire();

	UFUNCTION()
		void OnRep_HitscanTrace();

	void PlayImpactEffects(EPhysicalSurface SurfaceType, FVector ImpactPoint);

	//Weapons Status
	float LastFiredTime;
	float TimeBetweenShots;

	UPROPERTY(ReplicatedUsing=OnRep_HitscanTrace)
	FHitScanTrace HitScanTrace;

	//Weapon modifiers
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Modifers")
	float BaseDamage;

	/*RPM - Bullets per minute fired by weapon*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Modifers")
	float RateOfFire;

	FTimerHandle TimerHandle_TimeBetweenShots;


	//Weapon visual modifiers
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
		TSubclassOf<UDamageType> DamageType;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
		FName MuzzleSocketName;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
		FName TracerTargetName;


	//Weapons Particle Effects
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	UParticleSystem* MuzzleEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	UParticleSystem* DefaultImpactEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	UParticleSystem* FleshImpactEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	UParticleSystem* TracerEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<UCameraShake> FireCamShake;


public:	


	void StartFire();
	void StopFire();

	
};
