// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/UniformGridView.h"

#include "FunctionLibraries/WidgetManagerFunctionLibrary.h"

void UUniformGridView::SynchronizeProperties()
{
    Super::SynchronizeProperties();

#if WITH_EDITOR
    if (IsDesignTime())
    {
        RefreshDesignerItems();
    }
#endif
}

void UUniformGridView::SetEntriesNum(int32 NewEntriesNum)
{
    const int32 OldEntriesNum = GetEntriesNum();
    if (OldEntriesNum < NewEntriesNum)
    {
        for (int32 Index = 0; Index < NewEntriesNum - OldEntriesNum; ++Index)
        {
            AddDataObject(nullptr);
        }
    }
    else if (OldEntriesNum > NewEntriesNum)
    {
        RemoveEntries(OldEntriesNum - NewEntriesNum);
    }
}

void UUniformGridView::ClearEntries()
{
    for (const auto& [Index, Widget] : WidgetMap)
    {
        if (Widget) Widget->RemoveFromParent();
    }

    WidgetMap.Reset();
}

void UUniformGridView::AddDataObject(UObject* DataObject)
{
    if (EntryWidgetClass)
    {
        auto NewEntryWidget = CreateWidget<UUserWidget>(this, EntryWidgetClass);
        UWidgetManagerFunctionLibrary::SetDataObject(NewEntryWidget, DataObject);

        const int32 Index = WidgetMap.Num();
        WidgetMap.Emplace(Index, NewEntryWidget);

        const int32 Row = Index / MaxColumns;
        const int32 Column = Index % MaxColumns;
        AddChildToUniformGrid(NewEntryWidget, Row, Column);
    }
}

void UUniformGridView::SetDataObject(int32 Index, UObject* DataObject)
{
    if (WidgetMap.Contains(Index))
    {
        UWidgetManagerFunctionLibrary::SetDataObject(WidgetMap[Index], DataObject);
    }
}

void UUniformGridView::RemoveEntries(int32 Num)
{
    const int32 EntryNum = GetEntriesNum();
    for (int32 Index = EntryNum - 1; Index >= EntryNum - Num; --Index)
    {
        if (auto Widget = WidgetMap[Index])
        {
            Widget->RemoveFromParent();
        }

        WidgetMap.Remove(Index);
    }
}

#if WITH_EDITOR
void UUniformGridView::RefreshDesignerItems()
{
    ClearEntries();
    SetEntriesNum(NumDesignerPreviewEntries);
}
#endif

