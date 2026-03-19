// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SLAnimInstance.generated.h"

class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class SL_API USLAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	ACharacter* Character;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	UCharacterMovementComponent* MovementComponent;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Data")
	FVector Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Data")
	float GroundSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Data")
	bool bShouldMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Data")
	bool bIsFalling;

public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	UFUNCTION()
	void AnimNotify_ResetMovementInput();
	
};
