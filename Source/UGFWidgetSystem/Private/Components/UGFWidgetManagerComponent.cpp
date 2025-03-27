// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/UGFWidgetManagerComponent.h"

#include "Blueprint/UserWidget.h"
#include "Logging.h"
#include "GameFramework/PlayerState.h"

UUserWidget* UUGFWidgetManagerComponent::GetWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    if (WidgetMap.Contains(WidgetClass))
    {
        return WidgetMap[WidgetClass];
    }
    else
    {
        LOG_ACTOR_COMPONENT(Error, TEXT("%s is not exist."), *WidgetClass->GetName())

        return nullptr;
    }
}

void UUGFWidgetManagerComponent::ShowWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    // 유효성 검사
    if (WidgetClass == nullptr) return;

    // 위젯이 존재하지 않는 경우 생성
    if (!WidgetMap.Contains(WidgetClass)) RegisterWidget(WidgetClass);

    // 위젯 활성화
    if (UUserWidget* Widget = GetWidget(WidgetClass))
    {
        if (Widget->IsInViewport())
        {
            LOG_ACTOR_COMPONENT(Warning, TEXT("%s is already in viewport."), *WidgetClass->GetName())
        }
        else
        {
            Widget->AddToViewport();

            LOG_ACTOR_COMPONENT(Log, TEXT("%s is added to viewport."), *WidgetClass->GetName())
        }
    }
}

void UUGFWidgetManagerComponent::HideWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    // 유효성 검사
    if (WidgetClass == nullptr) return;

    // 위젯 비활성화
    if (UUserWidget* Widget = GetWidget(WidgetClass))
    {
        if (!Widget->IsInViewport())
        {
            LOG_ACTOR_COMPONENT(Warning, TEXT("%s is already not in viewport."), *WidgetClass->GetName())
        }
        else
        {
            Widget->RemoveFromParent();

            LOG_ACTOR_COMPONENT(Log, TEXT("%s is removed from viewport."), *WidgetClass->GetName())
        }
    }
}

void UUGFWidgetManagerComponent::ToggleWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    if (UUserWidget* Widget = GetWidget(WidgetClass))
    {
        if (Widget->IsInViewport())
        {
            HideWidget(WidgetClass);
        }
        else
        {
            ShowWidget(WidgetClass);
        }
    }
}

APlayerController* UUGFWidgetManagerComponent::GetPlayerController() const
{
    UClass* OwnerClass = GetOwner()->GetClass();

    if (OwnerClass->IsChildOf(APlayerController::StaticClass()))
    {
        APlayerController* PlayerController = Cast<APlayerController>(GetOwner());
        return PlayerController;
    }

    if (OwnerClass->IsChildOf(APawn::StaticClass()))
    {
        APawn* Pawn = Cast<APawn>(GetOwner());
        return Cast<APlayerController>(Pawn->Controller);
    }

    if (OwnerClass->IsChildOf(APlayerState::StaticClass()))
    {
        APlayerState* PlayerState = Cast<APlayerState>(GetOwner());
        return PlayerState->GetPlayerController();
    }

    return nullptr;
}

void UUGFWidgetManagerComponent::RegisterWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    // 유효성 검사
    if (WidgetClass == nullptr) return;

    // 중복 호출 방지
    if (WidgetMap.Contains(WidgetClass))
    {
        LOG_ACTOR_COMPONENT(Error, TEXT("%s is already registered."), *WidgetClass->GetName())
        return;
    }

    // 위젯 생성 및 등록
    UUserWidget* Widget = CreateWidget<UUserWidget>(GetPlayerController(), WidgetClass);
    WidgetMap.Emplace(WidgetClass, Widget);

    LOG_ACTOR_COMPONENT(Log, TEXT("%s is registered"), *WidgetClass->GetName())
}

void UUGFWidgetManagerComponent::UnRegisterWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    // 유효성 검사
    if (WidgetClass == nullptr) return;

    // 중복 호출 방지
    if (!WidgetMap.Contains(WidgetClass))
    {
        LOG_ACTOR_COMPONENT(Error, TEXT("%s is already unregistered."), *WidgetClass->GetName())
        return;
    }

    // 위젯 파괴 및 등록 해제
    HideWidget(WidgetClass);
    WidgetMap.Remove(WidgetClass);

    LOG_ACTOR_COMPONENT(Log, TEXT("%s is unregistered"), *WidgetClass->GetName())
}
