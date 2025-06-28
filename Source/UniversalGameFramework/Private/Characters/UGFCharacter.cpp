// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/UGFCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/CurrencyManagerComponent.h"
#include "Components/InputBinderComponent.h"
#include "Components/InteractionSystemComponentBase.h"
#include "Components/InventoryComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

const FName AUGFCharacter::CameraBoomName(TEXT("CameraBoom"));
const FName AUGFCharacter::FollowCameraName(TEXT("FollowCamera"));
const FName AUGFCharacter::InputBinderName(TEXT("InputBinder"));
const FName AUGFCharacter::InteractionSystemName(TEXT("InteractionSystem"));
const FName AUGFCharacter::CurrencyManagerName(TEXT("CurrencyManager"));
const FName AUGFCharacter::InventoryName(TEXT("Inventory"));

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

    /* CameraBoom */
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(CameraBoomName);
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 400.0f;
    CameraBoom->bUsePawnControlRotation = true;

    /* FollowCamera */
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(FollowCameraName);
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    /* InputBinder */
    InputBinder = CreateDefaultSubobject<UInputBinderComponent>(InputBinderName);

    /* InteractionSystem */
    InteractionSystem = CreateDefaultSubobject<UInteractionSystemComponentBase>(InteractionSystemName);

    /* CurrencyManager */
    CurrencyManager = CreateDefaultSubobject<UCurrencyManagerComponent>(CurrencyManagerName);

    /* Inventory */
    Inventory = CreateDefaultSubobject<UInventoryComponent>(InventoryName);
    Inventory->SetMaxSlotNum(20);
}

int32 AUGFCharacter::GetCurrency_Implementation(const FGameplayTag& CurrencyType) const
{
    return GetCurrencyManager()->GetCurrency(CurrencyType);
}

bool AUGFCharacter::AddCurrency_Implementation(const FGameplayTag& CurrencyType, int32 Quantity)
{
    return GetCurrencyManager()->AddCurrency(CurrencyType, Quantity);
}

bool AUGFCharacter::RemoveCurrency_Implementation(const FGameplayTag& CurrencyType, int32 Quantity)
{
    return GetCurrencyManager()->RemoveCurrency(CurrencyType, Quantity);
}

bool AUGFCharacter::AddProduct_Implementation(const TScriptInterface<IProductInterface>& Product, int32 Quantity)
{
    return GetInventory()->AddItem(Product.GetObject(), Quantity);
}

bool AUGFCharacter::RemoveProduct_Implementation(const TScriptInterface<IProductInterface>& Product, int32 Quantity)
{
    return GetInventory()->RemoveItem(Product.GetObject(), Quantity);
}
