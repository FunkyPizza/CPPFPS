// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SWeapon.h"
#include "SProjectileWeapon.generated.h"

/**
 * 
 */
UCLASS()
class CPPFPS_API ASProjectileWeapon : public ASWeapon
{
	GENERATED_BODY()
	
protected:

	//Weapon modifiers
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile Weapon")
		TSubclassOf<AActor> ProjectileClass;
	
	virtual void Fire() override;
};
