// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SLDefine.h"
#include "Components/ActorComponent.h"
#include "SLAttributeComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FDelegateOnAttributeChanged, ESLAttributeType, float)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SL_API USLAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FDelegateOnAttributeChanged OnAttributeChanged;

protected:
	UPROPERTY(EditAnywhere, Category = "Stamina")
	float CurrentStamina = 100.f;

	UPROPERTY(EditAnywhere, Category = "Stamina")
	float MaxStamina = 100.f;

	UPROPERTY(EditAnywhere, Category = "Stamina")
	float StaminaRegenRate = 0.5f;

	UPROPERTY()
	FTimerHandle StaminaRegenTimeHandler;

public:	
	USLAttributeComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FORCEINLINE float GetBaseStamina() const { return CurrentStamina; }
	FORCEINLINE float GetMaxStamina() const { return MaxStamina; }
	FORCEINLINE float GetStaminaRatio() const { return CurrentStamina / MaxStamina; }

public:
	bool CheckHasEnoughStamina(float StaminaCost) const;

	void DecreaseStamina(float StaminaCost);

	void ToggleStaminaRegeneration(bool bEnable, float StartDelay = 2.f);

	void BroadcastOnAttributeType(ESLAttributeType AttributeType) const;

private:
	void RegenrateStaminaHandler();
		
};
