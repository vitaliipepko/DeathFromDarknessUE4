// Death From Darkness. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DFDBaseCharacter.generated.h"

/*FORWARD DECLARATION*/
/*-----------------------------------------*/
class UCameraComponent;
class USkeletalMeshComponent;
/*-----------------------------------------*/


UCLASS()
class DEATHFROMDARKNESS_API ADFDBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADFDBaseCharacter();

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
/*-----------------------------------------*/

/*MOVEMENT FUNCTIONS*/
/*-----------------------------------------*/
	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void TurnAround(float Amount);
	void LookUp(float Amount);
	void StartCrouch();
	void StopCrouch();
/*-----------------------------------------*/

private:
	/** Socket Which Attaching Camera To Mesh */
	FName CameraSocket = "CameraSocket";

public:
	/** Return Camera Component */
	FORCEINLINE UCameraComponent* GetCamera() const { return CameraComponent; }

};
