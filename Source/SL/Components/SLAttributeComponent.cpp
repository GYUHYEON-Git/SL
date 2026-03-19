// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SLAttributeComponent.h"

USLAttributeComponent::USLAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void USLAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void USLAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

bool USLAttributeComponent::CheckHasEnoughStamina(float StaminaCost) const {
	return CurrentStamina >= StaminaCost;
}

void USLAttributeComponent::DecreaseStamina(float StaminaCost) {
	CurrentStamina = FMath::Clamp(CurrentStamina - StaminaCost, 0.f, MaxStamina);
	BroadcastOnAttributeType(ESLAttributeType::Stamina);
}

void USLAttributeComponent::ToggleStaminaRegeneration(bool bEnable, float StartDelay) {
	if (bEnable) {
		if (GetWorld()->GetTimerManager().IsTimerActive(StaminaRegenTimeHandler) == false) {
			GetWorld()->GetTimerManager().SetTimer(StaminaRegenTimeHandler, this, &ThisClass::RegenrateStaminaHandler, 0.1f, true, StartDelay);
		}
	}
	else {
		GetWorld()->GetTimerManager().ClearTimer(StaminaRegenTimeHandler);
	}
}

void USLAttributeComponent::BroadcastOnAttributeType(ESLAttributeType AttributeType) const {
	float Ratio = 0.f;
	switch (AttributeType) {
	case ESLAttributeType::Stamina:
		Ratio = GetStaminaRatio();
		break;
	case ESLAttributeType::Health:
		break;
	}
	OnAttributeChanged.Broadcast(AttributeType, Ratio);
}

void USLAttributeComponent::RegenrateStaminaHandler() {
	CurrentStamina = FMath::Clamp(CurrentStamina + StaminaRegenRate, 0.f, MaxStamina);
	BroadcastOnAttributeType(ESLAttributeType::Stamina);
	if (CurrentStamina >= MaxStamina) {
		ToggleStaminaRegeneration(false);
	}
}

