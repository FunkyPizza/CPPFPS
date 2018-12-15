// Fill out your copyright notice in the Description page of Project Settings.

#include "SExplosiveActor.h"
#include "DrawDebugHelpers.h"
#include "kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "SHealthComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Net/UnrealNetwork.h"


// Sets default values
ASExplosiveActor::ASExplosiveActor()
{

	HealthComp = CreateDefaultSubobject<USHealthComponent>(TEXT("HealthComponent"));


	//Create components
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ExplosiveMesh"));
	Mesh->SetMaterial(0, NormalMaterial);
	Mesh->SetCollisionObjectType(ECC_PhysicsBody);
	Mesh->SetSimulatePhysics(true);
	RootComponent = Mesh;


	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComponent"));
	RadialForceComp->SetupAttachment(RootComponent);
	RadialForceComp->Radius = 250.f;
	RadialForceComp->bImpulseVelChange = true;
	RadialForceComp->bAutoActivate = false;
	RadialForceComp->bIgnoreOwningActor = true;


	SetReplicates(true);
	SetReplicateMovement(true);
}

// Called when the game starts or when spawned
void ASExplosiveActor::BeginPlay()
{
	Super::BeginPlay();



	//Initialize variable
	bDied = false;
	HealthComp->OnHealthChanged.AddDynamic(this, &ASExplosiveActor::OnHealthChanged);
	
}


void ASExplosiveActor::OnHealthChanged(USHealthComponent* OwningHealthComp, float Health, float HealthDelta, const class UDamageType* DamageType,
	class AController* InstigatedBy, AActor* DamageCauser)
{
	if (bDied)
	{
		return;
	}

	if (Health <= 0)
	{
		OnRep_Exploded();

		bDied = true;

		Mesh->AddImpulse(400.f * GetActorUpVector(), NAME_None, true);

		RadialForceComp->FireImpulse();


	}
}

void ASExplosiveActor::OnRep_Exploded()
{
	Mesh->SetMaterial(0, ExplodedMaterial); //Changes the mesh's material

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticle, GetActorLocation()); //Play explosion particle effect
}

void ASExplosiveActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASExplosiveActor, bDied);
}




