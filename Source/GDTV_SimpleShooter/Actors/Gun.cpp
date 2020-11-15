// Fill out your copyright notice in the Description page of Project Settings.


#include "GDTV_SimpleShooter/Actors/Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh Component"));
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr) return false;

	// create temp variables to store the information
	FVector OwnerLocation;
	FRotator OwnerRotation;
	OwnerController->GetPlayerViewPoint(OwnerLocation, OwnerRotation);
	ShotDirection = -OwnerRotation.Vector();

	FVector EndPoint = OwnerLocation + OwnerRotation.Vector() * MaxRange;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(Hit, OwnerLocation, EndPoint, ECollisionChannel::ECC_GameTraceChannel1, Params);

}

void AGun::PullTrigger()
{
	// Spawn Muzzle VFX & SFX
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));

	FHitResult Hit;
	FVector ShotDirection;

	bool bHit = GunTrace(Hit, ShotDirection);

	if (bHit)
	{
		//Spawn Impact Effect
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Impact, Hit.Location, ShotDirection.Rotation());
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ImpactSound, Hit.Location, ShotDirection.Rotation());

		AActor* ActorHit = Hit.GetActor();
		AController* OwnerController = GetOwnerController();
		if (OwnerController == nullptr) return;

		if (ActorHit != nullptr && OwnerController != nullptr)
		{ 
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			float actualDamage = ActorHit->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}		
	}
	
}

AController* AGun::GetOwnerController() const
{
	// Get Owner (Player) to reach his (Player's) controller
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return nullptr;

	return OwnerPawn->GetController();
}
