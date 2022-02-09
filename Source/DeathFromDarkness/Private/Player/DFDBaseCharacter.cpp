// Death From Darkness. All Rights Reserved.


#include "Player/DFDBaseCharacter.h"
#include "Components/DFDCharacterMovementComponent.h"


ADFDBaseCharacter::ADFDBaseCharacter(const FObjectInitializer& ObjInit):Super(ObjInit.SetDefaultSubobjectClass<UDFDCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	
}

void ADFDBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADFDBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}