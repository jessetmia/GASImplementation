// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BasePlayerController.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Character/BasePlayerCharacter.h"
#include "GameFramework/Character.h"
#include "GameplayTags/BaseTags.h"

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!IsValid(Subsystem)) return;
	
	if (IsValid(ControllerContext))
	{
		Subsystem->AddMappingContext(ControllerContext, 0);
	}
	if (IsValid(AbilitiesContext))
	{
		Subsystem->AddMappingContext(AbilitiesContext, 0);
	}

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!IsValid(EnhancedInputComponent)) return;

	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ThisClass::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ThisClass::StopJump);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
	EnhancedInputComponent->BindAction(AdjustCameraAction, ETriggerEvent::Started, this, &ThisClass::AdjustCamera);
	EnhancedInputComponent->BindAction(ConfirmTargetAction, ETriggerEvent::Triggered, this, &ThisClass::ConfirmTarget);
	EnhancedInputComponent->BindAction(CancelTargetAction, ETriggerEvent::Triggered, this, &ThisClass::CancelTarget);
	EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ThisClass::SprintPressed);
	EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ThisClass::SprintReleased);
	EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Canceled, this, &ThisClass::SprintReleased);
	EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &ThisClass::CrouchPressed);
	EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &ThisClass::CrouchReleased);
	EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Canceled, this, &ThisClass::CrouchReleased);
	EnhancedInputComponent->BindAction(PrimaryAction, ETriggerEvent::Triggered, this, &ThisClass::ActivatePrimaryAbility);
}

void ABasePlayerController::SetUIInputMode()
{
	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);
	bShowMouseCursor = true;

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!IsValid(Subsystem)) return;

	Subsystem->RemoveMappingContext(ControllerContext);
	Subsystem->RemoveMappingContext(AbilitiesContext);
}

void ABasePlayerController::SetGameInputMode()
{
	const FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
	bShowMouseCursor = false;
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!IsValid(Subsystem)) return;

	Subsystem->AddMappingContext(ControllerContext, 1);
	Subsystem->AddMappingContext(AbilitiesContext, 0);
}

void ABasePlayerController::Jump()
{
	ActivateAbility(BaseTags::Movement::Jump);
}

void ABasePlayerController::StopJump()
{
	CancelAbility(BaseTags::Movement::Jump);
}

void ABasePlayerController::SprintPressed()
{
	ActivateAbility(BaseTags::Movement::Sprint);
}

void ABasePlayerController::SprintReleased()
{
	CancelAbility(BaseTags::Movement::Sprint);
}

void ABasePlayerController::CrouchPressed()
{
	ActivateAbility(BaseTags::Movement::Crouch);
}

void ABasePlayerController::CrouchReleased()
{
	CancelAbility(BaseTags::Movement::Crouch);
}

void ABasePlayerController::Move(const FInputActionValue& Value)
{
	if (!IsValid(GetPawn())) return;
	const FVector2D MoveVector = Value.Get<FVector2D>();

	const FRotator YawRotation(0, GetControlRotation().Yaw, 0);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	GetPawn()->AddMovementInput(ForwardDirection, MoveVector.Y);
	GetPawn()->AddMovementInput(RightDirection, MoveVector.X);
}

void ABasePlayerController::Look(const FInputActionValue& Value)
{
	if (!IsValid(GetPawn())) return;
	
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
}

void ABasePlayerController::ConfirmTarget()
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn());
	if (!IsValid(ASC)) return;

	ASC->InputConfirm();
}

void ABasePlayerController::CancelTarget()
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn());
	if (!IsValid(ASC)) return;

	ASC->InputCancel();
}

void ABasePlayerController::ActivateAbility(const FGameplayTag& AbilityTag) const
{
	if (!IsValid(GetCharacter())) return;
	
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn());
	if (!IsValid(ASC)) return;

	ASC->TryActivateAbilitiesByTag(AbilityTag.GetSingleTagContainer());
}

void ABasePlayerController::CancelAbility(const FGameplayTag& AbilityTag) const
{
	if (!IsValid(GetCharacter())) return;
}

void ABasePlayerController::ActivatePrimaryAbility()
{
	ActivateAbility(BaseTags::Abilities::Categories::Primary);
}

void ABasePlayerController::AdjustCamera(const FInputActionValue& Value)
{
	ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(GetPawn());
	if (!IsValid(PlayerCharacter)) return;
	
	// float ArmLength = PlayerCharacter->GetArmLength();
	// ArmLength= FMath::Clamp(ArmLength + (Value.Get<float>() * 10.0), 200.f, 500.f);
	// PlayerCharacter->AdjustCamera(ArmLength);
}
