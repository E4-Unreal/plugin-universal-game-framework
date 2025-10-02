// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/UGFPlayerCharacter.h"


#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/PawnWidgetManagerComponent.h"
#include "Components/CurrencyManagerComponent.h"
#include "Components/InputBinderComponent.h"
#include "Components/InteractionSystemComponent.h"
#include "Components/InventoryComponent.h"
#include "Components/EquipmentManagerComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Games/UGFSaveGame.h"
#include "Subsystems/SaveGameSubsystem.h"
#include "Components/WeaponManagerComponent.h"
#include "FunctionLibraries/ItemDataFunctionLibrary.h"

const FName AUGFPlayerCharacter::CameraBoomName(TEXT("CameraBoom"));
const FName AUGFPlayerCharacter::FollowCameraName(TEXT("FollowCamera"));
const FName AUGFPlayerCharacter::OverlapSphereName(TEXT("OverlapSphere"));
const FName AUGFPlayerCharacter::InputBinderName(TEXT("InputBinder"));
const FName AUGFPlayerCharacter::InteractionSystemName(TEXT("InteractionSystem"));
const FName AUGFPlayerCharacter::CurrencyManagerName(TEXT("CurrencyManager"));
const FName AUGFPlayerCharacter::InventoryName(TEXT("Inventory"));
const FName AUGFPlayerCharacter::EquipmentManagerName(TEXT("EquipmentManager"));
const FName AUGFPlayerCharacter::PawnWidgetManagerName(TEXT("PawnWidgetManager"));
const FName AUGFPlayerCharacter::WeaponManagerName(TEXT("WeaponManager"));

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
    GetOverlapSphere()->InitSphereRadius(128.0f);

    /* InputBinder */

    InputBinder = CreateDefaultSubobject<UInputBinderComponent>(InputBinderName);

    /* InteractionSystem */

    InteractionSystem = CreateDefaultSubobject<UInteractionSystemComponent>(InteractionSystemName);

    /* Inventory */

    Inventory = CreateDefaultSubobject<UInventoryComponent>(InventoryName);
    GetInventory()->MaxSlotNum = 20;

    /* CurrencyManager */

    CurrencyManager = CreateDefaultSubobject<UCurrencyManagerComponent>(CurrencyManagerName);

    /* EquipmentManager */

    EquipmentManager = CreateOptionalDefaultSubobject<UEquipmentManagerComponent>(EquipmentManagerName);

    /* PawnWidgetManager */

    PawnWidgetManager = CreateDefaultSubobject<UPawnWidgetManagerComponent>(PawnWidgetManagerName);

    /* WeaponManager */

    WeaponManager = CreateDefaultSubobject<UWeaponManagerComponent>(WeaponManagerName);
}

void AUGFPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (USaveGameSubsystem* DataManagerSubsystem = GetGameInstance()->GetSubsystem<USaveGameSubsystem>())
    {
        DataManagerSubsystem->OnSaveDataDelegate.AddDynamic(this, &ThisClass::OnSaveData);
        DataManagerSubsystem->OnLoadDataDelegate.AddDynamic(this, &ThisClass::OnLoadData);

        OnLoadData(DataManagerSubsystem->GetSaveGame());
    }
}

int32 AUGFPlayerCharacter::GetCurrency_Implementation(const FGameplayTag& CurrencyType) const
{
    return GetCurrencyManager()->GetCurrencyByType(CurrencyType);
}

bool AUGFPlayerCharacter::AddCurrency_Implementation(const FGameplayTag& CurrencyType, int32 Quantity)
{
    return GetCurrencyManager()->AddCurrencyByType(CurrencyType, Quantity);
}

bool AUGFPlayerCharacter::RemoveCurrency_Implementation(const FGameplayTag& CurrencyType, int32 Quantity)
{
    return GetCurrencyManager()->RemoveCurrencyByType(CurrencyType, Quantity);
}

bool AUGFPlayerCharacter::AddProduct_Implementation(UDataDefinitionBase* Product, int32 Quantity)
{
    if (auto ItemInstance = UItemDataFunctionLibrary::CreateItemInstance(Product))
    {
        UItemDataFunctionLibrary::SetQuantity(ItemInstance, Quantity);
        return GetInventory()->AddContent(ItemInstance);
    }

    return false;
}

bool AUGFPlayerCharacter::RemoveProduct_Implementation(UDataDefinitionBase* Product, int32 Quantity)
{
    if (auto ItemInstance = UItemDataFunctionLibrary::CreateItemInstance(Product))
    {
        UItemDataFunctionLibrary::SetQuantity(ItemInstance, Quantity);
        return GetInventory()->RemoveContent(ItemInstance);
    }

    return false;
}

void AUGFPlayerCharacter::OnSaveData_Implementation(USaveGame* SaveGame)
{
    if (!IsPlayerControlled()) return;

    if (UUGFSaveGame* CastedSaveGame = Cast<UUGFSaveGame>(SaveGame))
    {
        CastedSaveGame->CurrencyMap = GetCurrencyManager()->GetCurrencyMap();
    }
}

void AUGFPlayerCharacter::OnLoadData_Implementation(USaveGame* SaveGame)
{
    if (!IsPlayerControlled()) return;

    if (UUGFSaveGame* CastedSaveGame = Cast<UUGFSaveGame>(SaveGame))
    {
        GetCurrencyManager()->SetCurrencyMap(CastedSaveGame->CurrencyMap);
    }
}
