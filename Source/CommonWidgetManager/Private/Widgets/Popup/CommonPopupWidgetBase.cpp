// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Popup/CommonPopupWidgetBase.h"

#include "CommonTextBlock.h"

void UCommonPopupWidgetBase::SetTitleText_Implementation(const FText& TitleText)
{
    if (GetTitleTextBlock())
    {
        GetTitleTextBlock()->SetText(TitleText);
    }
}

void UCommonPopupWidgetBase::SetMessageText_Implementation(const FText& MessageText)
{
    if (GetMessageTextBlock())
    {
        GetMessageTextBlock()->SetText(MessageText);
    }
}
