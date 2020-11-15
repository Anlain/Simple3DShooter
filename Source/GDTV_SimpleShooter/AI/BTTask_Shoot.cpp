// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AIController.h"
#include "../Characters/ShooterCharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
    NodeName = FString(TEXT("Shoot"));
}

// Command the AI Controlled Character to shoot at player
EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    // Get hold of the AIController
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (AIController == nullptr) { EBTNodeResult::Failed; }

    // Get hold of the possessed pawn and cast it to ShooterCharacter
    AShooterCharacter* AIShooterCharacter = Cast<AShooterCharacter>(AIController->GetPawn());
    if (AIShooterCharacter == nullptr) { EBTNodeResult::Failed; }

    // FIRE !!!
    AIShooterCharacter->Shoot();
    return EBTNodeResult::Succeeded;
}
