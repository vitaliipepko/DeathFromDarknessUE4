// Death From Darkness. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/DFDBaseCharacter.h"
#include "DFDPlayerCharacter.generated.h"

/*Forward Declaration*/
/*-----------------------------------------*/
class UCameraComponent;
class USkeletalMeshComponent;
class UDFDInteractionComponent;
class UCameraShakeBase;
/*-----------------------------------------*/

/** Interaction Data Structure */
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
/*-----------------------------------------*/


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

/*------------------------------------------------------PROTECTED-----------------------------------------------------*/
protected:
	/*PROPERTIES*/
	/*-----------------------------------------*/
	/** Camera Property */
	UPROPERTY(EditAnywhere, Category = "Components")
	UCameraComponent* CameraComponent;

	/** Mesh Properties */
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

	/** CameraShake Property */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CameraShake")
	TSubclassOf<UCameraShakeBase> CameraShakeRun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CameraShake")
	TSubclassOf<UCameraShakeBase> CameraShakeOnLanded;

	/** Interaction Properties */
	UPROPERTY(EditDefaultsOnly, Category="Interaction")
	float InteractionCheckFrequency;
	
	UPROPERTY(EditDefaultsOnly, Category="Interaction")
	float InteractionCheckDistance;
	/*-----------------------------------------*/


	/** Interaction Struct */
	UPROPERTY()
	FInteractionData InteractionData;

	/** Timer for Interaction */
	FTimerHandle InteractTimerHandle;


	//Interaction Functions
	/*-----------------------------------------*/
	void PerformInteractionCheck();
	void CouldFindInteractable();
	void FoundNewInteractable(UDFDInteractionComponent* Interactable);
	void BeginInteract();
	void EndInteract();
	void Interact();
	/*-----------------------------------------*/

/*------------------------------------------------------PRIVATE-------------------------------------------------------*/
private:
	/** Movement Functions and Variables */
	/*-----------------------------------------*/
	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void TurnAround(float Amount);
	void LookUp(float Amount);
	void ToggleCrouch();
	void StartRunning();
	void StopRunning();

	/** When Player Touch Land */
	UFUNCTION()
	void OnGroundLanded(const FHitResult& HitResult);

	/** Play CameraShakeBase */
	/*-----------------------------------------*/
	void PlayCameraShake(TSubclassOf<UCameraShakeBase> CameraShake) const;
	/*-----------------------------------------*/

	/** Movement Variables */
	/*-----------------------------------------*/
	bool WantsToRun;
	bool IsMovingForward;
	bool bIsCrouching;
	/*-----------------------------------------*/

	/** Mouse sensitivity */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mouse Sensitivity", meta = (AllowPrivateAccess = "true"))
	float MouseSensitivity;
	/*-----------------------------------------*/
	
	/** Socket Which Attaching Camera To Mesh */
	/*-----------------------------------------*/
	FName CameraSocket = "CameraSocket";
	/*-----------------------------------------*/

/*-------------------------------------------------------PUBLIC-------------------------------------------------------*/
public:
	/** Interaction Functions */
	/*-----------------------------------------*/
	bool IsInteracting() const;
	float GetRemainingInteractingTime() const;
	/*-----------------------------------------*/

	/** Return Interactable Component */
	/*-----------------------------------------*/
	FORCEINLINE UDFDInteractionComponent* GetInteractable() const { return InteractionData.ViewedInteractionComponent; }
	/*-----------------------------------------*/
	
	/** Return Camera Component */
	/*-----------------------------------------*/
	UFUNCTION(BlueprintPure, Category="Camera")
	FORCEINLINE UCameraComponent* GetCamera() const { return CameraComponent; }
	/*-----------------------------------------*/

	/** Return Running Player Or Not */
	/*-----------------------------------------*/
	UFUNCTION(BlueprintPure, Category="Movement")
	FORCEINLINE bool IsRunning() const;
	/*-----------------------------------------*/

	/** Return Crouching Player Or Not */
	/*-----------------------------------------*/
	UFUNCTION(BlueprintPure, Category="Movement")
	FORCEINLINE bool IsCrouching() const { return bIsCrouching; }
	/*-----------------------------------------*/
};
