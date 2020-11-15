// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "../Controllers/ShooterAIController.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);
	//UE_LOG(LogTemp, Warning, TEXT("A Pawn Died."));

	// check if the pawn killed was a player
	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController != nullptr)
	{
		EndGame(false);
	}

	// its not a player, check if there are some ShooterAICharacters alive
	// for loop over shooterAI in World:
	for (AShooterAIController* AIController : TActorRange<AShooterAIController>(GetWorld()))
	{
		// Is not dead?
		if (!AIController->IsDead()) { return; }
	}

	// end game (true)
	EndGame(true);
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
	// "for each" controller from a range of controllers in this level
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);

		/*
		* Too complicated code
		// player won
		if (bIsPlayerWinner)
		{
			// player's controller
			if (Controller->IsPlayerController()) { Controller->GameHasEnded(nullptr, true); continue; }
			// AI's controller
			Controller->GameHasEnded(nullptr, false); 
			continue;
		}
		// player lost
		else
		{
			// player's controller
			if (Controller->IsPlayerController()) { Controller->GameHasEnded(nullptr, false); continue; }
			// AI's controller
			Controller->GameHasEnded(nullptr, true);
			continue;
		}
		*/
	}
}
