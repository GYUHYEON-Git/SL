// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SLDefine.h"
#include "Blueprint/UserWidget.h"
#include "SLPlayerHUDWidget.generated.h"

class USLStatBarWidget;
/**
 * 
 */
UCLASS()
class SL_API USLPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	TObjectPtr<USLStatBarWidget> StaminaBarWidget;

public:
	USLPlayerHUDWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void NativeConstruct() override;

	void OnAttributeChanged(ESLAttributeType AttributeType, float InValue);
	
};
