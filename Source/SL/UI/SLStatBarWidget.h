// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SLStatBarWidget.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS()
class SL_API USLStatBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	TObjectPtr<UProgressBar> StatBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor FillColorAndOpacity = FLinearColor::Green;

public:
	USLStatBarWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void NativePreConstruct() override;

	void SetRatio(float Ratio) const;

};
