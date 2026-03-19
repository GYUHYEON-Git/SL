// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SLCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "UI/SLPlayerHUDWidget.h"
#include "SLGameplayTags.h"

#include "Components/SLAttributeComponent.h"
#include "Components/SLStateComponent.h"

ASLCharacter::ASLCharacter() {
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);

	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("StringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeRotation(FRotator(-30.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 400.f;
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;

	AttributeComponent = CreateDefaultSubobject<USLAttributeComponent>(TEXT("Attribute"));
	StateComponent = CreateDefaultSubobject<USLStateComponent>(TEXT("State"));
}

void ASLCharacter::BeginPlay() {
	Super::BeginPlay();
	if (PlayerHUDWidgetClass) {
		PlayerHUDWidget = CreateWidget<USLPlayerHUDWidget>(GetWorld(), PlayerHUDWidgetClass);
		if (PlayerHUDWidget) {
			PlayerHUDWidget->AddToViewport();
		}
	}

}

void ASLCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void ASLCharacter::NotifyControllerChanged() {
	Super::NotifyControllerChanged();
	if (APlayerController* PC = Cast<APlayerController>(GetController())) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer())) {
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ASLCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);

		EnhancedInputComponent->BindAction(SprintRollingAction, ETriggerEvent::Triggered, this, &ThisClass::Sprinting);
		EnhancedInputComponent->BindAction(SprintRollingAction, ETriggerEvent::Completed, this, &ThisClass::StopSprint);
		EnhancedInputComponent->BindAction(SprintRollingAction, ETriggerEvent::Canceled, this, &ThisClass::Rolling);
	}

}

void ASLCharacter::Move(const FInputActionValue& Values) {
	check(StateComponent);
	//if (StateComponent->MovementInputEnabled() == false) return;
	FVector2D MovementVector = Values.Get<FVector2D>();
	if (Controller != nullptr) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardVector, MovementVector.Y);
		AddMovementInput(RightVector, MovementVector.X);
	}
}

void ASLCharacter::Look(const FInputActionValue& Values) {
	FVector2D LookDirection = Values.Get<FVector2D>();
	if (Controller != nullptr) {
		AddControllerPitchInput(LookDirection.Y);
		AddControllerYawInput(LookDirection.X);
	}
}

bool ASLCharacter::IsMoving() const {
	if (UCharacterMovementComponent* CharacterMovementComponent = GetCharacterMovement()) {
		return CharacterMovementComponent->Velocity.Size2D() > 3.f && CharacterMovementComponent->GetCurrentAcceleration() != FVector::Zero();
	}
	return false;
}

void ASLCharacter::Sprinting() {
	if (AttributeComponent->GetBaseStamina() > 5.f && IsMoving()) {
		AttributeComponent->ToggleStaminaRegeneration(false);
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
		AttributeComponent->DecreaseStamina(0.1f);
	}
	else {
		StopSprint();
	}
}

void ASLCharacter::StopSprint() {
	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	AttributeComponent->ToggleStaminaRegeneration(true);
}

void ASLCharacter::Rolling() {
	check(AttributeComponent);
	check(StateComponent);
	if (AttributeComponent->CheckHasEnoughStamina(15.f)) {
		AttributeComponent->ToggleStaminaRegeneration(false);
		StateComponent->ToggleMovementInput(false);
		AttributeComponent->DecreaseStamina(15.f);
		PlayAnimMontage(RollingMontage);
		StateComponent->SetState(SLGameplayTags::Character_State_Rolling);
		AttributeComponent->ToggleStaminaRegeneration(true, 1.5f);
	}
}
