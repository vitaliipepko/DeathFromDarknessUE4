// Death From Darkness. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/DFDBaseCharacter.h"
#include "DFDPlayerCharacter.generated.h"

/*FORWARD DECLARATION*/
/*-----------------------------------------*/
class UCameraComponent;
class USkeletalMeshComponent;
class UDFDInteractionComponent;
/*-----------------------------------------*/


USTRUCT()
struct FInteractionData
{
	GENERATED_USTRUCT_BODY()

	FInteractionData()
	{
		ViewedInteractionComponent = nullptr;
		LastInteractionCheckTime = 0.f;
		bInteractHeld = false;
	}

	UPROPERTY()
	UDFDInteractionComponent* ViewedInteractionComponent;

	UPROPERTY()
	float LastInteractionCheckTime;

	UPROPERTY()
	bool bInteractHeld;
	
};


UCLASS()
class DEATHFROMDARKNESS_API ADFDPlayerCharacter : public ADFDBaseCharacter
{
	GENERATED_BODY()

public:
	ADFDPlayerCharacter(const FObjectInitializer& ObjInit);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	/*PROPERTIES*/
	/*-----------------------------------------*/
	UPROPERTY(EditAnywhere, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	USkeletalMeshComponent* HairMesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	USkeletalMeshComponent* BodyMesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	USkeletalMeshComponent* PantsMesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	USkeletalMeshComponent* HandsMesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	USkeletalMeshComponent* LegsMesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	USkeletalMeshComponent* ShoesMesh;

	UPROPERTY(EditDefaultsOnly, Category="Interaction")
	float InteractionCheckFrequency;
	
	UPROPERTY(EditDefaultsOnly, Category="Interaction")
	float InteractionCheckDistance;

	
	UPROPERTY()
	FInteractionData InteractionData;

	FTimerHandle InteractTimerHandle;


	//INTERACTION FUNCTIONS
	void PerformInteractionCheck();
	void CouldFindInteractable();
	void FoundNewInteractable(UDFDInteractionComponent* Interactable);
	void BeginInteract();
	void EndInteract();
	void Interact();
	/*-----------------------------------------*/

private:
	/*MOVEMENT FUNCTIONS*/
	/*-----------------------------------------*/
	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void TurnAround(float Amount);
	void LookUp(float Amount);
	void ToggleCrouch();
	void StartRunning();
	void StopRunning();
	
	bool WantsToRun = false;
    bool IsMovingForward = false;
	bool bIsCrouching;

	/** Socket Which Attaching Camera To Mesh */
	FName CameraSocket = "CameraSocket";

public:
	//INTERACTION FUNCTIONS
	bool IsInteracting() const;
	float GetRemainingInteractingTime() const;

	
	FORCEINLINE UDFDInteractionComponent* GetInteractable() const { return InteractionData.ViewedInteractionComponent; }
	
	/** Return Camera Component */
	UFUNCTION(BlueprintPure, Category="Camera")
	FORCEINLINE UCameraComponent* GetCamera() const { return CameraComponent; }

	/** Return Running Player Or Not */
	UFUNCTION(BlueprintPure, Category="Movement")
	FORCEINLINE bool IsRunning() const;

	/** Return Crouching Player Or Not */
	UFUNCTION(BlueprintPure, Category="Movement")
	FORCEINLINE bool IsCrouching() const { return bIsCrouching; }
};
