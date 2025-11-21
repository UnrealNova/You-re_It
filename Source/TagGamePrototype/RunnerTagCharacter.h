// RunnerTagCharacter.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RunnerTagCharacter.generated.h"


class UCameraComponent;
class USpringArmComponent;

// Forward declarations for Enhanced Input
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class TAGGAMEPROTOTYPE_API ARunnerTagCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    // Constructor
    ARunnerTagCharacter();

protected:
    virtual void BeginPlay() override;

    /** Enhanced Input callbacks */
    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);

    /** Tag State */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tag")
    bool bIsIt = false;

    /** Input assets (assign in Blueprint) */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
    UInputMappingContext* DefaultMappingContext;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
    UInputAction* MoveAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
    UInputAction* LookAction;

public:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    /** Camera Boom */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    USpringArmComponent* CameraBoom;

    /** Follow Camera */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    UCameraComponent* FollowCamera;

    /** Let Blueprints toggle Tag state */
    UFUNCTION(BlueprintCallable, Category = "Tag")
    void SetIsIt(bool NewState);

    /** Get Tag state */
    UFUNCTION(BlueprintCallable, Category = "Tag")
    bool IsIt() const { return bIsIt; }
};
