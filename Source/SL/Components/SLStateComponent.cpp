// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SLStateComponent.h"

#include "Kismet/KismetSystemLibrary.h"

USLStateComponent::USLStateComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void USLStateComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void USLStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void USLStateComponent::ToggleMovementInput(bool bEnabled, float Duration) {
	if (bEnabled) {
		FLatentActionInfo LatentAction;
		LatentAction.CallbackTarget = this;
		LatentAction.ExecutionFunction = "MovementInputEnableAction";
		LatentAction.Linkage = 0;
		LatentAction.UUID = 0;
		UKismetSystemLibrary::RetriggerableDelay(GetWorld(), Duration, LatentAction);
	}
	else {
		bMovementInputEnabled = false;
	}
}

void USLStateComponent::MovementInputEnableAction() {
	bMovementInputEnabled = true;
	ClearState();
}

void USLStateComponent::ClearState() {
	CurrentState = FGameplayTag::EmptyTag;

}

bool USLStateComponent::IsCrrentStateEqualToAny(const FGameplayTagContainer& TagsToCheck) const {
	return TagsToCheck.HasTagExact(CurrentState);
}

