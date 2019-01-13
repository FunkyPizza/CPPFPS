// Fill out your copyright notice in the Description page of Project Settings.

#include "SPickupQctor.h"
#include "Components/SphereComponent.h"
#include "Components/DecalComponent.h"
#include "SPowerupActor.h"


// Sets default values
ASPickupQctor::ASPickupQctor()
{

 SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
 SphereComp->SetSphereRadius(75);
 RootComponent = SphereComp;


 DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
 DecalComp->SetRelativeRotation(FRotator(90, 0.0f, 0.0f));
 DecalComp->DecalSize = FVector(64, 75, 75);
 DecalComp->SetupAttachment(RootComponent);

 CooldownDuration = 10.0f,

	 SetReplicates(true);

}

// Called when the game starts or when spawned
void ASPickupQctor::BeginPlay()
{
	Super::BeginPlay();

	if (Role == ROLE_Authority)
	{
		Respawn();
	}	

}

void ASPickupQctor::Respawn()
{
	if (PowerUpClass == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("PowerUpClass is nullptr in %s. Please update your Blueprint"), *GetName());
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	PowerUpInstance = GetWorld()->SpawnActor<ASPowerupActor>(PowerUpClass, GetTransform(), SpawnParams);
}

void ASPickupQctor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (Role == ROLE_Authority && PowerUpInstance)
	{
		PowerUpInstance->ActivatePowerup(OtherActor);
		PowerUpInstance = nullptr;

		//Set a timer to respawn
		GetWorldTimerManager().SetTimer(TimerHandle_Respawn, this, &ASPickupQctor::Respawn, CooldownDuration);
	}

}

