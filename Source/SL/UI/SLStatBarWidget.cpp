// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SLStatBarWidget.h"

#include "Components/ProgressBar.h"


USLStatBarWidget::USLStatBarWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer) {}

void USLStatBarWidget::NativePreConstruct() {
	Super::NativePreConstruct();
	if (StatBar) {
		StatBar->SetFillColorAndOpacity(FillColorAndOpacity);
	}
}

void USLStatBarWidget::SetRatio(float Ratio) const {
	if (StatBar) {
		StatBar->SetPercent(Ratio);
	}
}
