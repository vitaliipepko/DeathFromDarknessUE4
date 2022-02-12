// Death From Darkness. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DFDCharacterMovementComponent.generated.h"


UCLASS()
class DEATHFROMDARKNESS_API UDFDCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	/** Modifier Character speed in Blueprint */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "1.5", ClampMax = "10.0"))
	float RunModifier = 4.0f;

	virtual float GetMaxSpeed() const override;
};
