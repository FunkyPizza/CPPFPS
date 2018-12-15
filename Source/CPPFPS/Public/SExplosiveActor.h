// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SExplosiveActor.generated.h"

class UStaticMeshComponent;
class USHealthComponent;
class URadialForceComponent;
class UParticleSystem;
class UMaterial;


UCLASS()
class CPPFPS_API ASExplosiveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASExplosiveActor();

protected:

	//Class components
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		USHealthComponent* HealthComp;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		URadialForceComponent* RadialForceComp;

	// Functions
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHealthChanged(USHealthComponent* OwningHealthComp, float Health, float HealthDelta, const class UDamageType* DamageType, 
		class AController* InstigatedBy, AActor* DamageCauser);

	//Modifiers
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Modifiers")
		float ImpulseRadius;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Modifiers")
		float ImpulseIntensity;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Modifiers")
		UParticleSystem* ExplosionParticle;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Modifiers")
		UMaterial* NormalMaterial;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Modifiers")
		UMaterial* ExplodedMaterial;

	//Variables
	UPROPERTY(ReplicatedUsing = OnRep_Exploded)
	bool bDied;

	UFUNCTION()
		void OnRep_Exploded();

public:	


	
	
};
