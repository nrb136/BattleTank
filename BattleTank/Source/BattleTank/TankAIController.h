// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
	ATank* GetControlledAITank() const;

	void BeginPlay() override;

	void Tick(float DeltaTime) override;

	ATank* GetPlayerTank() const;


	
	
};
