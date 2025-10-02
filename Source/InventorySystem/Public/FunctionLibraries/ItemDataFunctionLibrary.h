// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ItemDataFunctionLibrary.generated.h"

class UDataDefinitionBase;
class UDataInstanceBase;
struct FGameplayTag;

/**
 *
 */
UCLASS()
class INVENTORYSYSTEM_API UItemDataFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    /* ItemData */

    UFUNCTION(BlueprintPure, Category = "ItemData")
    static UDataAsset* GetItemData(UDataDefinitionBase* Definition);

    UFUNCTION(BlueprintPure, Category = "ItemData")
    static int32 GetMaxStack(UDataDefinitionBase* Definition);

    UFUNCTION(BlueprintPure, Category = "ItemData")
    static FGameplayTag GetItemType(UDataDefinitionBase* Definition);

    /* ItemInstanceData */

    UFUNCTION(BlueprintPure, Category = "ItemInstanceData")
    static UDataInstanceBase* CreateItemInstance(UDataDefinitionBase* Definition);

    UFUNCTION(BlueprintPure, Category = "ItemInstanceData")
    static UObject* GetItemInstance(UDataInstanceBase* DataInstance);

    UFUNCTION(BlueprintPure, Category = "ItemInstanceData")
    static int32 GetQuantity(UDataInstanceBase* DataInstance);

    UFUNCTION(BlueprintCallable, Category = "ItemInstanceData")
    static void SetQuantity(UDataInstanceBase* DataInstance, int32 NewQuantity);
};
