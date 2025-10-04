// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/UniformGridPanel.h"
#include "UniformGridView.generated.h"

/**
 *
 */
UCLASS()
class WIDGETMANAGER_API UUniformGridView : public UUniformGridPanel
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (DesignerRebuild, MustImplement = "EntryWidgetInterface"))
    TSubclassOf<UUserWidget> EntryWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (DesignerRebuild, ClampMin = 1))
    int32 MaxColumns = 4;

#if WITH_EDITORONLY_DATA
    UPROPERTY(EditAnywhere, Category = "Config", meta = (DesignerRebuild, ClampMin = 0))
    int32 NumDesignerPreviewEntries = 20;
#endif

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TMap<int32, TObjectPtr<UUserWidget>> WidgetMap;

public:
    /* Widget */

    virtual void SynchronizeProperties() override;

    /* API */

    UFUNCTION(BlueprintPure)
    virtual int32 GetEntriesNum() const { return WidgetMap.Num(); }

    UFUNCTION(BlueprintCallable)
    virtual void SetEntriesNum(int32 NewEntriesNum);

    UFUNCTION(BlueprintCallable)
    virtual void ClearEntries();

    UFUNCTION(BlueprintCallable)
    virtual void AddItem(UObject* Item);

    UFUNCTION(BlueprintCallable)
    virtual void SetItem(int32 Index, UObject* Item);

    UFUNCTION(BlueprintCallable)
    virtual void RemoveEntries(int32 Num);

protected:
#if WITH_EDITOR
    virtual void RefreshDesignerItems();
#endif
};
