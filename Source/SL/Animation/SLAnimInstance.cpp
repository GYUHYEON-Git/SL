// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/SLAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/SLCharacter.h"
#include "Components/SLStateComponent.h"

void USLAnimInstance::NativeInitializeAnimation() {
	Super::NativeInitializeAnimation();
	Character = Cast<ACharacter>(GetOwningActor());
	if (Character) {
		MovementComponent = Character->GetCharacterMovement();
	}
}

void USLAnimInstance::NativeUpdateAnimation(float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (Character == nullptr) return;
	if (MovementComponent == nullptr) return;
	Velocity = MovementComponent->Velocity;
	GroundSpeed = Velocity.Size2D();
	bShouldMove = GroundSpeed > 3.f && MovementComponent->GetCurrentAcceleration() != FVector::ZeroVector;
	bIsFalling = MovementComponent->IsFalling();
}

void USLAnimInstance::AnimNotify_ResetMovementInput() {
	if (const TObjectPtr<ASLCharacter> LocalCharacter = Cast<ASLCharacter>(GetOwningActor())) {
		LocalCharacter->GetStateComponent()->ToggleMovementInput(true);
	}
}
