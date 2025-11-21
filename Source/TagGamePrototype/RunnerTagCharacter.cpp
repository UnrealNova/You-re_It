// RunnerTagCharacter.cpp

#include "RunnerTagCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"

// Enhanced Input
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Components/InputComponent.h"
#include "Engine/LocalPlayer.h"
#include "Engine/Engine.h" // for GEngine, FColor

// Constructor: When the character is born, set up their body and behavior.
ARunnerTagCharacter::ARunnerTagCharacter()
{
    // Allow this character to run code every frame if I ever want to override Tick()
    PrimaryActorTick.bCanEverTick = true;

    // Creates Camera Boom
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 250.0f;
    CameraBoom->bUsePawnControlRotation = true;

    // Create the Follow Camera - The main camera the player sees through
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom);
    FollowCamera->bUsePawnControlRotation = false; // The camera doesn't interpret the control rotation directly

    // Get character movement defaults
    GetCharacterMovement()->bOrientRotationToMovement = true;  // Character automatically faces movement direction
    bUseControllerRotationYaw = false;                         // Don’t rotate directly from controller yaw

    // Start not being "It"
    bIsIt = false;
}

void ARunnerTagCharacter::BeginPlay()
{
    Super::BeginPlay();

    // Add the input mapping context to the local player
    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        if (ULocalPlayer* LP = PC->GetLocalPlayer())
        {
            if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
            {
                if (DefaultMappingContext)
                {
                    Subsystem->AddMappingContext(DefaultMappingContext, 0);
                }
            }
        }
    }
}

void ARunnerTagCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        if (MoveAction)
        {
            EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARunnerTagCharacter::Move);
        }

        if (LookAction)
        {
            EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARunnerTagCharacter::Look);
        }
    }
}

void ARunnerTagCharacter::Move(const FInputActionValue& Value)
{
    // Value is a 2D vector for movement input
    const FVector2D MovementVector = Value.Get<FVector2D>();

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(
            -1,
            0.f,
            FColor::Yellow,
            FString::Printf(TEXT("Move: X=%f Y=%f"), MovementVector.X, MovementVector.Y)
        );
    }

    if (Controller && (MovementVector.SizeSquared() > 0.f))
    {
        const FRotator ControlRot = Controller->GetControlRotation();
        const FRotator YawRot(0.f, ControlRot.Yaw, 0.f);

        const FVector ForwardDir = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
        const FVector RightDir = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);

        AddMovementInput(ForwardDir, MovementVector.Y); // Y = forward/back (W/S)
        AddMovementInput(RightDir, MovementVector.X); // X = right/left (D/A)
    }
}

void ARunnerTagCharacter::Look(const FInputActionValue& Value)
{
    const FVector2D LookAxisVector = Value.Get<FVector2D>();

    AddControllerYawInput(LookAxisVector.X);   // mouse X / controller X
    AddControllerPitchInput(LookAxisVector.Y); // mouse Y / controller Y
}

void ARunnerTagCharacter::SetIsIt(bool NewState)
{
    bIsIt = NewState;

    // Later you can add:
    // - change speed
    // - swap material
    // - play SFX/VFX
    // For now it's just storing the state.
}
