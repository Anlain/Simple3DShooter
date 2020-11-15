// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GDTV_SimpleShooterGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class GDTV_SIMPLESHOOTER_API AGDTV_SimpleShooterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn* PawnKilled);
	
};
