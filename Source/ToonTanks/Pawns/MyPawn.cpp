// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Components/CapsuleComponent.h"
#include "ToonTanks/Actors/ProjectileBase.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void AMyPawn::RotateTurret(FVector TargetLocation) 
{
	FVector TargetLocationClean = FVector(TargetLocation.X, TargetLocation.Y, TurretMesh->GetComponentLocation().Z);
	FVector TurretStartLocation = TurretMesh->GetComponentLocation();
	FRotator TurretRotation = FVector(TargetLocationClean - TurretStartLocation).Rotation();
	TurretMesh->SetWorldRotation(TurretRotation);
}

void AMyPawn::Fire() 
{
	if (ProjectileClass)
	{
		FVector ProjectileInitLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator ProjectileInitRotation = ProjectileSpawnPoint->GetComponentRotation();
		AProjectileBase* Projectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, ProjectileInitLocation, ProjectileInitRotation);
		Projectile->SetOwner(this);
	}
}

void AMyPawn::HandleDestruction() 
{
	
}



