// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetActions/WidgetPaletteCategoryUtility.h"

#include "Blueprint/UserWidget.h"

UWidgetPaletteCategoryUtility::UWidgetPaletteCategoryUtility()
{
    SupportedClasses.Emplace(UUserWidget::StaticClass());
}
