// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
	HUD->RemoveFromViewport();

	UUserWidget* EndScreen;

	if (bIsWinner) { EndScreen = CreateWidget(this, WinScreenClass); }
	else		   { EndScreen = CreateWidget(this, LoseScreenClass); }

	if (EndScreen != nullptr) { EndScreen->AddToViewport(); }

	GetWorldTimerManager().SetTimer(RestartHandle, this, &APlayerController::RestartLevel, RestartDelay);
}

void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Create HUD widget and add it to viewport
	HUD = CreateWidget(this, HUDClass);
	if (HUD != nullptr) { HUD->AddToViewport(); }

}
