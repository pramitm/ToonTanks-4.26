// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyPawn.h"
#include "MyPawnTurret.generated.h"

class AMyPawnTank;

UCLASS()
class TOONTANKS_API AMyPawnTurret : public AMyPawn
{
	GENERATED_BODY()

private:

	AMyPawnTank* PlayerPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRate = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess =  "true"))
	float FireRange = 100.f;

	FTimerHandle FireRateTimerHandle;

	void CheckFireCondition();
	float ReturnDistanceToPlayer();

public:

	AMyPawnTurret();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void HandleDestruction() override;
};
