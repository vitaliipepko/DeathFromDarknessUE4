// Death From Darkness. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DFDBaseCharacter.generated.h"


UCLASS()
class DEATHFROMDARKNESS_API ADFDBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADFDBaseCharacter(const FObjectInitializer& ObjInit);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
};
