// Death From Darkness. All Rights Reserved.


#include "Player/DFDPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/DFDInteractionComponent.h"
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

	InteractionCheckFrequency = 0.f;
	InteractionCheckDistance = 100.f;
}

void ADFDPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADFDPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PerformInteractionCheck();
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

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ADFDPlayerCharacter::BeginInteract);
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &ADFDPlayerCharacter::EndInteract);
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


/*ITERACTION FUNCTIONS*/
/////////////////////////////////////////////
/*-----------------------------------------*/
void ADFDPlayerCharacter::PerformInteractionCheck()
{
	if(!GetWorld() && !GetController()) return;

	InteractionData.LastInteractionCheckTime = GetWorld()->GetTimeSeconds();

	FVector EyesLocation;
	FRotator EyesRotation;

	GetController()->GetPlayerViewPoint(EyesLocation, EyesRotation);

	FVector TraceStart = EyesLocation;
	FVector TraceEnd = (EyesRotation.Vector() * InteractionCheckDistance) + TraceStart;
	FHitResult TraceHit;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(TraceHit, TraceStart, TraceEnd, ECC_Visibility, QueryParams);
	if(TraceHit.GetActor())
	{
		UDFDInteractionComponent* InteractionComponent =
			Cast<UDFDInteractionComponent>(TraceHit.GetActor()->GetComponentByClass(UDFDInteractionComponent::StaticClass()));
		if(InteractionComponent)
		{
			float Distance = (TraceStart - TraceHit.ImpactPoint).Size();
			
			if(InteractionComponent != GetInteractable() && Distance <= InteractionComponent->InteractionDistance)
			{
				FoundNewInteractable(InteractionComponent);
			}
			else if(Distance > InteractionComponent->InteractionDistance && GetInteractable())
			{
				CouldFindInteractable();
			}

			return;
		}
	}

	CouldFindInteractable();
}
/*-----------------------------------------*/

/*-----------------------------------------*/
void ADFDPlayerCharacter::CouldFindInteractable()
{
	if(GetWorldTimerManager().IsTimerActive(InteractTimerHandle))
	{
		GetWorldTimerManager().ClearTimer(InteractTimerHandle);
	}

	UDFDInteractionComponent* Interactable = GetInteractable();
	if(Interactable)
	{
		Interactable->EndFocus(this);

		if(InteractionData.bInteractHeld)
		{
			EndInteract();
		}
	}

	InteractionData.ViewedInteractionComponent = nullptr;
}
/*-----------------------------------------*/

/*-----------------------------------------*/
void ADFDPlayerCharacter::FoundNewInteractable(UDFDInteractionComponent* Interactable)
{
	EndInteract();
	
	UDFDInteractionComponent* OldInteractable = GetInteractable();
	if(OldInteractable)
	{
		OldInteractable->EndFocus(this);
	}
	
	InteractionData.ViewedInteractionComponent = Interactable;
	Interactable->BeginFocus(this);
}
/*-----------------------------------------*/

/*-----------------------------------------*/
void ADFDPlayerCharacter::BeginInteract()
{
	InteractionData.bInteractHeld = true;

	UDFDInteractionComponent* Interactable = GetInteractable();
	if(Interactable)
	{
		Interactable->BeginInteract(this);
		if(FMath::IsNearlyZero(Interactable->InteractionTime))
		{
			Interact();
		}
		else
		{
			GetWorldTimerManager().SetTimer(InteractTimerHandle, this, &ADFDPlayerCharacter::Interact,
				Interactable->InteractionTime, false);
		}
	}
}
/*-----------------------------------------*/

/*-----------------------------------------*/
void ADFDPlayerCharacter::EndInteract()
{
	InteractionData.bInteractHeld = false;

	GetWorldTimerManager().ClearTimer(InteractTimerHandle);

	UDFDInteractionComponent* Interactable = GetInteractable();
	if(Interactable)
	{
		Interactable->EndInteract(this);
	}
}
/*-----------------------------------------*/

/*-----------------------------------------*/
void ADFDPlayerCharacter::Interact()
{
	GetWorldTimerManager().ClearTimer(InteractTimerHandle);

	UDFDInteractionComponent* Interactable = GetInteractable();
	if(Interactable)
	{
		Interactable->Interact(this);
	}
}
/*-----------------------------------------*/

/*-----------------------------------------*/
bool ADFDPlayerCharacter::IsInteracting() const
{
	return GetWorldTimerManager().IsTimerActive(InteractTimerHandle);
}
/*-----------------------------------------*/

/*-----------------------------------------*/
float ADFDPlayerCharacter::GetRemainingInteractingTime() const
{
	return GetWorldTimerManager().GetTimerRemaining(InteractTimerHandle);
}
/*-----------------------------------------*/
/////////////////////////////////////////////