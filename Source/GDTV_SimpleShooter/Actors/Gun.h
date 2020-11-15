// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

class USkeletalMeshComponent;
class UParticleSystem;

UCLASS()
class GDTV_SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PullTrigger();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Visual Effects")
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere, Category = "Visual Effects")
	UParticleSystem* Impact;

	UPROPERTY(EditAnywhere, Category = "Sound Effects")
	USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere, Category = "Sound Effects")
	USoundBase* ImpactSound;

	UPROPERTY(EditAnywhere, Category = "Weapon Stats")
	float MaxRange = 10000.0f;

	UPROPERTY(EditAnywhere, Category = "Weapon Stats")
	float Damage = 24.0f;

	bool GunTrace(FHitResult& Hit, FVector& ShotDirection);

	AController* GetOwnerController() const;

};
