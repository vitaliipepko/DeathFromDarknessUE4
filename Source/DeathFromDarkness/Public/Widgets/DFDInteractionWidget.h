// Death From Darkness. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DFDInteractionWidget.generated.h"

/*Forward Declaration*/
/*-----------------------------------------*/
class UDFDInteractionComponent;
/*-----------------------------------------*/


UCLASS()
class DEATHFROMDARKNESS_API UDFDInteractionWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category="Interaction")
	void UpdateInteractionWidget(UDFDInteractionComponent* InteractionComponent);

	UFUNCTION(BlueprintImplementableEvent)
	void OnUpdateInteractionWidget();

	UPROPERTY(BlueprintReadOnly, Category="Interaction", meta=(ExposeOnSpawn))
	UDFDInteractionComponent* OwningInteractionComponent;
};
