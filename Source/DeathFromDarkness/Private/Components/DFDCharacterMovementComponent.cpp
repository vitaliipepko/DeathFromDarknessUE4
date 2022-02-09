// Death From Darkness. All Rights Reserved.


#include "Components/DFDCharacterMovementComponent.h"
#include "Player/DFDPlayerCharacter.h"


float UDFDCharacterMovementComponent::GetMaxSpeed() const
{
	const float MaxSpeed = Super::GetMaxSpeed();
	const ADFDPlayerCharacter* Player = Cast<ADFDPlayerCharacter>(GetPawnOwner());
	return Player && Player->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed;
}
