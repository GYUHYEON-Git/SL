// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SLPlayerHUDWidget.h"

#include "Components/SLAttributeComponent.h"
#include "UI/SLStatBarWidget.h"

USLPlayerHUDWidget::USLPlayerHUDWidget(const FObjectInitializer& ObjectInitializer) 
	:Super(ObjectInitializer) {}

void USLPlayerHUDWidget::NativeConstruct() {
	if (TObjectPtr<APawn> Pawn = GetOwningPlayerPawn()) {
		if (TObjectPtr<USLAttributeComponent> Attribute = Pawn->GetComponentByClass<USLAttributeComponent>()) {
			Attribute->OnAttributeChanged.AddUObject(this, &ThisClass::OnAttributeChanged);
			Attribute->BroadcastOnAttributeType(ESLAttributeType::Stamina);
		}
	}
}

void USLPlayerHUDWidget::OnAttributeChanged(ESLAttributeType AttributeType, float InValue) {
	switch (AttributeType) {
	case ESLAttributeType::Stamina:
		StaminaBarWidget->SetRatio(InValue);
		break;
	case ESLAttributeType::Health:
		break;
	}
}
