// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/UGFPlayerCharacter.h"


#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/CurrencyManagerComponent.h"
#include "Components/InputBinderComponent.h"
#include "Components/InteractionSystemComponent.h"
#include "Components/InventoryComponent.h"
#include "Components/WidgetManagerComponent.h"
#include "EquipmentManager/Public/Components/EquipmentManagerComponent.h"
#include "GameFramework/SpringArmComponent.h"

const FName AUGFPlayerCharacter::CameraBoomName(TEXT("CameraBoom"));
const FName AUGFPlayerCharacter::FollowCameraName(TEXT("FollowCamera"));
const FName AUGFPlayerCharacter::OverlapSphereName(TEXT("OverlapSphere"));
const FName AUGFPlayerCharacter::InputBinderName(TEXT("InputBinder"));
const FName AUGFPlayerCharacter::InteractionSystemName(TEXT("InteractionSystem"));
const FName AUGFPlayerCharacter::CurrencyManagerName(TEXT("CurrencyManager"));
const FName AUGFPlayerCharacter::InventoryName(TEXT("Inventory"));
const FName AUGFPlayerCharacter::EquipmentManagerName(TEXT("EquipmentManager"));
const FName AUGFPlayerCharacter::WidgetManagerName(TEXT("WidgetManager"));

AUGFPlayerCharacter::AUGFPlayerCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* CameraBoom */

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(CameraBoomName);
    GetCameraBoom()->SetupAttachment(RootComponent);
    GetCameraBoom()->TargetArmLength = 400.0f;
    GetCameraBoom()->bUsePawnControlRotation = true;

    /* FollowCamera */

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(FollowCameraName);
    GetFollowCamera()->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    GetFollowCamera()->bUsePawnControlRotation = false;

    /* OverlapSphere */

    OverlapSphere = CreateDefaultSubobject<USphereComponent>(OverlapSphereName);
    GetOverlapSphere()->SetupAttachment(GetCapsuleComponent());

    /* InputBinder */

    InputBinder = CreateDefaultSubobject<UInputBinderComponent>(InputBinderName);

    /* InteractionSystem */

    InteractionSystem = CreateDefaultSubobject<UInteractionSystemComponent>(InteractionSystemName);

    /* Inventory */

    Inventory = CreateDefaultSubobject<UInventoryComponent>(InventoryName);
    GetInventory()->SetMaxSlotNum(20);

    /* CurrencyManager */

    CurrencyManager = CreateDefaultSubobject<UCurrencyManagerComponent>(CurrencyManagerName);

    /* EquipmentManager */

    EquipmentManager = CreateOptionalDefaultSubobject<UEquipmentManagerComponent>(EquipmentManagerName);

    /* WidgetManager */

    WidgetManager = CreateDefaultSubobject<UWidgetManagerComponent>(WidgetManagerName);
}

int32 AUGFPlayerCharacter::GetCurrency_Implementation(const FGameplayTag& CurrencyType) const
{
    return GetCurrencyManager()->GetCurrency(CurrencyType);
}

bool AUGFPlayerCharacter::AddCurrency_Implementation(const FGameplayTag& CurrencyType, int32 Quantity)
{
    return GetCurrencyManager()->AddCurrency(CurrencyType, Quantity);
}

bool AUGFPlayerCharacter::RemoveCurrency_Implementation(const FGameplayTag& CurrencyType, int32 Quantity)
{
    return GetCurrencyManager()->RemoveCurrency(CurrencyType, Quantity);
}

bool AUGFPlayerCharacter::AddProduct_Implementation(const TScriptInterface<IProductInterface>& Product, int32 Quantity)
{
    return GetInventory()->AddItem(Product.GetObject(), Quantity);
}

bool AUGFPlayerCharacter::RemoveProduct_Implementation(const TScriptInterface<IProductInterface>& Product, int32 Quantity)
{
    return GetInventory()->RemoveItem(Product.GetObject(), Quantity);
}
