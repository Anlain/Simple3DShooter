// Fill out your copyright notice in the Description page of Project Settings.


#include "GDTV_SimpleShooter/Controllers/ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Characters/ShooterCharacter.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();
	if (AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);

		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AShooterAIController::IsDead() const
{
	AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(GetPawn());
	if (ControlledCharacter != nullptr)
	{
		return ControlledCharacter->IsDead();
	}
	// if a controlled doesnt control a pawn, it was already detached -> his pawn is dead
	return true;
}
