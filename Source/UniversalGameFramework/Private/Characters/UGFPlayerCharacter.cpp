// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/UGFPlayerCharacter.h"


#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/CommonPawnWidgetManagerComponent.h"
#include "Components/CurrencyManagerComponent.h"
#include "Components/InputBinderComponent.h"
#include "Components/InteractionSystemComponent.h"
#include "Components/InventoryComponent.h"
#include "Components/WidgetManagerComponent.h"
#include "Components/EquipmentManagerComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Games/UGFSaveGame.h"
#include "Subsystems/DataManagerSubsystem.h"

const FName AUGFPlayerCharacter::CameraBoomName(TEXT("CameraBoom"));
const FName AUGFPlayerCharacter::FollowCameraName(TEXT("FollowCamera"));
const FName AUGFPlayerCharacter::OverlapSphereName(TEXT("OverlapSphere"));
const FName AUGFPlayerCharacter::InputBinderName(TEXT("InputBinder"));
const FName AUGFPlayerCharacter::InteractionSystemName(TEXT("InteractionSystem"));
const FName AUGFPlayerCharacter::CurrencyManagerName(TEXT("CurrencyManager"));
const FName AUGFPlayerCharacter::InventoryName(TEXT("Inventory"));
const FName AUGFPlayerCharacter::EquipmentManagerName(TEXT("EquipmentManager"));
const FName AUGFPlayerCharacter::CommonPawnWidgetManagerName(TEXT("CommonPawnWidgetManager"));

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

    /* CommonPawnWidgetManager */

    CommonPawnWidgetManager = CreateDefaultSubobject<UCommonPawnWidgetManagerComponent>(CommonPawnWidgetManagerName);
}

void AUGFPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (UDataManagerSubsystem* DataManagerSubsystem = GetGameInstance()->GetSubsystem<UDataManagerSubsystem>())
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

bool AUGFPlayerCharacter::AddProduct_Implementation(const TScriptInterface<IProductInterface>& Product, int32 Quantity)
{
    FItemInstance NewItem = FItemInstance(Product.GetObject(), Quantity);
    return GetInventory()->AddItem(NewItem);
}

bool AUGFPlayerCharacter::RemoveProduct_Implementation(const TScriptInterface<IProductInterface>& Product, int32 Quantity)
{
    FItemInstance NewItem = FItemInstance(Product.GetObject(), Quantity);
    return GetInventory()->RemoveItem(NewItem);
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
