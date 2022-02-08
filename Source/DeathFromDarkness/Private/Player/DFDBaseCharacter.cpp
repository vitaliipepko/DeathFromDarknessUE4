// Death From Darkness. All Rights Reserved.


#include "Player/DFDBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


ADFDBaseCharacter::ADFDBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(GetMesh(), CameraSocket);
	CameraComponent->bUsePawnControlRotation = true;

	HairMesh = CreateDefaultSubobject<USkeletalMeshComponent>("HairMeshComponent");
	HairMesh->SetupAttachment(GetMesh());

	BodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>("BodyMeshComponent");
	BodyMesh->SetupAttachment(GetMesh());

	PantsMesh = CreateDefaultSubobject<USkeletalMeshComponent>("PantsMeshComponent");
	PantsMesh->SetupAttachment(GetMesh());

	HandsMesh = CreateDefaultSubobject<USkeletalMeshComponent>("HandsMeshComponent");
	HandsMesh->SetupAttachment(GetMesh());

	LegsMesh = CreateDefaultSubobject<USkeletalMeshComponent>("LegsMeshComponent");
	LegsMesh->SetupAttachment(GetMesh());

	ShoesMesh = CreateDefaultSubobject<USkeletalMeshComponent>("ShoesMeshComponent");
	ShoesMesh->SetupAttachment(GetMesh());

	SprintSpeed = 450.f;
	WalkSpeed = 120.f;
}

void ADFDBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADFDBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADFDBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADFDBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADFDBaseCharacter::MoveRight);

	PlayerInputComponent->BindAxis("TurnAround", this, &ADFDBaseCharacter::TurnAround);
	PlayerInputComponent->BindAxis("LookUp", this, &ADFDBaseCharacter::LookUp);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ADFDBaseCharacter::ToggleCrouch);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ADFDBaseCharacter::StartSprinting);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ADFDBaseCharacter::StopSprinting);
}

/*MOVEMENT FUNCTIONS*/
/////////////////////////////////////////////
/*-----------------------------------------*/
void ADFDBaseCharacter::MoveForward(float Amount)
{
	if (Amount == 0) return;
	AddMovementInput(GetActorForwardVector(), Amount);
}
/*-----------------------------------------*/

/*-----------------------------------------*/
void ADFDBaseCharacter::MoveRight(float Amount)
{
	if (Amount == 0) return;
	AddMovementInput(GetActorRightVector(), Amount);
}
/*-----------------------------------------*/

/*-----------------------------------------*/
void ADFDBaseCharacter::TurnAround(float Amount)
{
	if (Amount == 0) return;
	AddControllerYawInput(Amount);
}
/*-----------------------------------------*/

/*-----------------------------------------*/
void ADFDBaseCharacter::LookUp(float Amount)
{
	if (Amount == 0) return;
	AddControllerPitchInput(Amount);
}
/*-----------------------------------------*/

/*-----------------------------------------*/
void ADFDBaseCharacter::ToggleCrouch()
{
	if(GetCharacterMovement()->IsCrouching())
	{
		UnCrouch();
	}
	else
	{
		GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
		Crouch();
	}
}
/*-----------------------------------------*/

/*-----------------------------------------*/
void ADFDBaseCharacter::StartSprinting()
{
	SetSprinting(true);
	UE_LOG(LogTemp, Warning, TEXT("%f"), SprintSpeed);
}
/*-----------------------------------------*/

/*-----------------------------------------*/
void ADFDBaseCharacter::StopSprinting()
{
	SetSprinting(false);
	UE_LOG(LogTemp, Warning, TEXT("%f"), WalkSpeed);
}
/*-----------------------------------------*/

/*-----------------------------------------*/
void ADFDBaseCharacter::SetSprinting(bool bNewSprinting)
{
	if (!CanSprint()) return;
	
	bIsSprinting = bNewSprinting;
	
	GetCharacterMovement()->MaxWalkSpeed = bIsSprinting ? SprintSpeed : WalkSpeed;
}
/*-----------------------------------------*/

/*-----------------------------------------*/
bool ADFDBaseCharacter::CanSprint() const
{
	return !bIsCrouched;
}
/*-----------------------------------------*/

/*-----------------------------------------*/
bool ADFDBaseCharacter::IsRunning() const
{
	return bIsSprinting;
}
/*-----------------------------------------*/
/////////////////////////////////////////////