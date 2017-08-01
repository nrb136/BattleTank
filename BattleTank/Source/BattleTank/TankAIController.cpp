// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	ATank* PlayerTank = GetPlayerTank();
	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AITank cant find player"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AITank found player %s"), *(PlayerTank->GetName()));
	}

}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (GetPlayerTank()) {
		GetControlledAITank()->AimAt(GetPlayerTank()->GetActorLocation());
	}
}

ATank* ATankAIController::GetControlledAITank() const {
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const {
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) {
		return nullptr;
	}
	return Cast<ATank>(PlayerPawn);
}



