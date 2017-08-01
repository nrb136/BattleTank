// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	ATank* ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank"));
	}
	else {
		
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing %s"), *(ControlledTank->GetName()));

	}
}

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
	
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetControlledTank()) {
		return;
	}

	FVector OutHitLocation;
	if (GetSightRayHitLocation(OutHitLocation)) {
		GetControlledTank()->AimAt(OutHitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const {
	

	// Find crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX*CrosshairXLocation, ViewportSizeY*CrosshairYLocation);


	FVector PlayerLocation = GetControlledTank()->GetActorLocation();
	//FVector PlayerRotation = 
	//OutHitLocation = PlayerLocation + PlayerRotation;
	FVector LookDirection, HitResult;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		//UE_LOG(LogTemp, Warning, TEXT("LookDirection: %s"), *LookDirection.ToString());
	}
	if (GetLookVectorHitLocation(LookDirection, OutHitLocation)) {
	}

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {
	FVector WorldLocation;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		WorldLocation,
		LookDirection
	);
		
	
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const {
	FHitResult OutHit;
	
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + FVector(LookDirection*LineTraceRange);
	ECollisionChannel TraceChannel = ECC_Visibility;
	
	if (GetWorld()->LineTraceSingleByChannel(
		OutHit,
		StartLocation,
		EndLocation,
		TraceChannel
	)) {
		HitLocation = OutHit.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;

}


