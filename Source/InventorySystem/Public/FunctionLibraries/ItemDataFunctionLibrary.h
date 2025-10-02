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
    static bool HasItemData(UDataDefinitionBase* Definition);

    UFUNCTION(BlueprintPure, Category = "ItemData")
    static int32 GetMaxStack(UDataDefinitionBase* Definition);

    UFUNCTION(BlueprintPure, Category = "ItemData")
    static FGameplayTag GetItemType(UDataDefinitionBase* Definition);

    /* ItemInstance */

    UFUNCTION(BlueprintPure, Category = "ItemInstance")
    static UDataInstanceBase* CreateItemInstance(UDataDefinitionBase* Definition);

    UFUNCTION(BlueprintPure, Category = "ItemInstance")
    static bool HasItemInstance(UDataInstanceBase* Instance);

    UFUNCTION(BlueprintPure, Category = "ItemInstance")
    static int32 GetQuantity(UDataInstanceBase* Instance);

    UFUNCTION(BlueprintCallable, Category = "ItemInstance")
    static void SetQuantity(UDataInstanceBase* Instance, int32 NewQuantity);

protected:
    static UDataAsset* GetItemData(UDataDefinitionBase* Definition);
    static UObject* GetItemInstance(UDataInstanceBase* Instance);
};
