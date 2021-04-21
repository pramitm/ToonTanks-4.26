// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#define OUT

AMyPawnTank::AMyPawnTank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void AMyPawnTank::BeginPlay()
{
	Super::BeginPlay();

    PlayerControllerRef = Cast<APlayerController>(GetController());
}

void AMyPawnTank::HandleDestruction() 
{
    Super::HandleDestruction();
    // TO DO: Hide player pawn components
}

// Called every frame
void AMyPawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    Rotate();
    Move();

    FHitResult TraceResult;
    PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, OUT TraceResult);

    RotateTurret(TraceResult.ImpactPoint);
}

// Called to bind functionality to input
void AMyPawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &AMyPawnTank::CalculateMoveInput);
    PlayerInputComponent->BindAxis("Turn", this, &AMyPawnTank::CalculateRotateInput);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMyPawnTank::Fire);
}

void AMyPawnTank::CalculateMoveInput(float Value)
{
    MoveDirection = FVector(Value * MoveSpeed * GetWorld()->GetDeltaSeconds(), 0, 0);
}

void AMyPawnTank::CalculateRotateInput(float Value) 
{
    FRotator Rotation = FRotator(0, Value * RotateSpeed * GetWorld()->GetDeltaSeconds(), 0);
    RotateDirection = FQuat(Rotation);
}

void AMyPawnTank::Move() 
{
    AddActorLocalOffset(MoveDirection, true);
}

void AMyPawnTank::Rotate() 
{
    AddActorLocalRotation(RotateDirection, true);
}
