// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/UGFCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Components/MontageManagerComponent.h"
#include "Components/SocketManagerComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

const FName AUGFCharacter::SocketManagerName(TEXT("SocketManager"));
const FName AUGFCharacter::MontageManagerName(TEXT("MontageManager"));

AUGFCharacter::AUGFCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* Pawn */

    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    /* CapsuleComponent */

    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    /* CharacterMovement */

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
    GetCharacterMovement()->JumpZVelocity = 700.f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->MaxWalkSpeed = 500.f;
    GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
    GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

    /* SocketManager */

    SocketManager = CreateDefaultSubobject<USocketManagerComponent>(SocketManagerName);
    GetSocketManager()->DataAssetType = "CharacterSocket";

    /* MontageManager */

    MontageManager = CreateDefaultSubobject<UMontageManagerComponent>(MontageManagerName);
}
