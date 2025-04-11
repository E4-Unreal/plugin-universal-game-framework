// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ItemDefinition.h"

#include "EditorAssetLibrary.h"

#if WITH_EDITOR
bool UItemDefinition::SetData(const FItemDefinitionData& InData)
{
    if (Data == InData) return false;
    Data = InData;

    GetPackage()->FullyLoad();
    UEditorAssetLibrary::SaveLoadedAsset(this);

    return true;
}
#endif

