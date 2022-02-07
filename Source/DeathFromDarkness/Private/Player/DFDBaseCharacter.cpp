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

	TorsoMesh = CreateDefaultSubobject<USkeletalMeshComponent>("TorsoMeshComponent");
	TorsoMesh->SetupAttachment(GetMesh());

	HandsMesh = CreateDefaultSubobject<USkeletalMeshComponent>("HandsMeshComponent");
	HandsMesh->SetupAttachment(GetMesh());

	LegsMesh = CreateDefaultSubobject<USkeletalMeshComponent>("LegsMeshComponent");
	LegsMesh->SetupAttachment(GetMesh());

	PantsMesh = CreateDefaultSubobject<USkeletalMeshComponent>("PantsMeshComponent");
	PantsMesh->SetupAttachment(GetMesh());

	ShoesMesh = CreateDefaultSubobject<USkeletalMeshComponent>("ShoesMeshComponent");
	ShoesMesh->SetupAttachment(GetMesh());

	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
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

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ADFDBaseCharacter::StartCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ADFDBaseCharacter::StopCrouch);
}

/*MOVABLE FUNCTIONS*/
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
void ADFDBaseCharacter::StartCrouch()
{
	Crouch();
}
/*-----------------------------------------*/

/*-----------------------------------------*/
void ADFDBaseCharacter::StopCrouch()
{
	UnCrouch();
}
/*-----------------------------------------*/
/////////////////////////////////////////////