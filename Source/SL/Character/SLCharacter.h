// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SLCharacter.generated.h"

struct FInputActionValue;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class USLPlayerHUDWidget;
class USLAttributeComponent;
class USLStateComponent;

UCLASS()
class SL_API ASLCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> LookAction;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> SprintRollingAction;

protected:
	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<UAnimMontage> RollingMontage;

protected:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<USLPlayerHUDWidget> PlayerHUDWidgetClass;

	UPROPERTY()
	TObjectPtr<USLPlayerHUDWidget> PlayerHUDWidget;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USLAttributeComponent> AttributeComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USLStateComponent> StateComponent;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Movement Data")
	float NormalSpeed = 500.f;

	UPROPERTY(VisibleAnywhere, Category = "Movement Data")
	float SprintSpeed = 750.f;

public:
	ASLCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyControllerChanged() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	FORCEINLINE TObjectPtr<USLStateComponent> GetStateComponent() const { return StateComponent; }

public:

	void Move(const FInputActionValue& Values);

	void Look(const FInputActionValue& Values);

protected:
	bool IsMoving() const;

	void Sprinting();

	void StopSprint();

	void Rolling();
};
