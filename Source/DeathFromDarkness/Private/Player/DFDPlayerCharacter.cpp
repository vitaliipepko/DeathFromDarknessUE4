// Death From Darkness. All Rights Reserved.


#include "Player/DFDPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


ADFDPlayerCharacter::ADFDPlayerCharacter(const FObjectInitializer& ObjInit):Super(ObjInit)
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
}

void ADFDPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADFDPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADFDPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADFDPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADFDPlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("TurnAround", this, &ADFDPlayerCharacter::TurnAround);
	PlayerInputComponent->BindAxis("LookUp", this, &ADFDPlayerCharacter::LookUp);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ADFDPlayerCharacter::ToggleCrouch);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ADFDPlayerCharacter::StartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ADFDPlayerCharacter::StopRunning);
}

/*MOVEMENT FUNCTIONS*/
/////////////////////////////////////////////
/*-----------------------------------------*/
void ADFDPlayerCharacter::MoveForward(float Amount)
{
	if (Amount ==  0.f) return;
	IsMovingForward = Amount > 0.f;
	AddMovementInput(GetActorForwardVector(), Amount);
}
/*-----------------------------------------*/

/*-----------------------------------------*/
void ADFDPlayerCharacter::MoveRight(float Amount)
{
	if (Amount ==  0.f) return;
	AddMovementInput(GetActorRightVector(), Amount);
}
/*-----------------------------------------*/

/*-----------------------------------------*/
void ADFDPlayerCharacter::TurnAround(float Amount)
{
	if (Amount == 0.f) return;
	AddControllerYawInput(Amount);
}
/*-----------------------------------------*/

/*-----------------------------------------*/
void ADFDPlayerCharacter::LookUp(float Amount)
{
	if (Amount ==  0.f) return;
	AddControllerPitchInput(Amount);
}
/*-----------------------------------------*/

/*-----------------------------------------*/
void ADFDPlayerCharacter::ToggleCrouch()
{
	if(GetCharacterMovement()->IsCrouching())
	{
		UnCrouch();
		bIsCrouching = false;
	}
	else
	{
		GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
		Crouch();
		bIsCrouching = true;
	}
}
/*-----------------------------------------*/

/*-----------------------------------------*/
void ADFDPlayerCharacter::StartRunning()
{
	WantsToRun = true;
}
/*-----------------------------------------*/

/*-----------------------------------------*/
void ADFDPlayerCharacter::StopRunning()
{
	WantsToRun = false;
}
/*-----------------------------------------*/

/*-----------------------------------------*/
bool ADFDPlayerCharacter::IsRunning() const
{
	return WantsToRun && IsMovingForward && !bIsCrouching && !GetVelocity().IsZero();
}
/*-----------------------------------------*/
/////////////////////////////////////////////