// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "MyPawnTank.h"

AMyPawnTurret::AMyPawnTurret() 
{
    
}

void AMyPawnTurret::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

    if (!PlayerPawn || ReturnDistanceToPlayer() > FireRange)
    {
        return;
    }

    this->RotateTurret(PlayerPawn->GetActorLocation());
}

void AMyPawnTurret::BeginPlay() 
{
	Super::BeginPlay();
    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &AMyPawnTurret::CheckFireCondition, FireRate, true, 0);

    PlayerPawn = Cast<AMyPawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void AMyPawnTurret::HandleDestruction() 
{
    Super::HandleDestruction();

    Destroy();
}

void AMyPawnTurret::CheckFireCondition() 
{
    //UE_LOG(LogTemp, Warning, TEXT("Check fire condition!"));

    //If Player == null || player is dead then return
    if (!PlayerPawn)
    {
        UE_LOG(LogTemp, Error, TEXT("Player pawn not found"));
        return;
    }
    //If player is within range then fire
    if (ReturnDistanceToPlayer() <= FireRange)
    {
        Fire();
    }
}

float AMyPawnTurret::ReturnDistanceToPlayer() 
{
    if (!PlayerPawn)
    {
        return FireRange + 1;
    }

    float Distance = FVector::Dist(PlayerPawn->GetActorLocation(), this->GetActorLocation());

    //UE_LOG(LogTemp, Warning, TEXT("Distance from turret = %f"), Distance);

    return Distance;
}
