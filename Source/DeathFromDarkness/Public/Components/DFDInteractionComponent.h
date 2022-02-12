// Death From Darkness. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "DFDInteractionComponent.generated.h"

/** Forward Declaration */
/*-----------------------------------------*/
class ADFDPlayerCharacter;
/*-----------------------------------------*/

/** Interaction Delegates */
/*-----------------------------------------*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeginInteract, ADFDPlayerCharacter*, Character);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEndInteract, ADFDPlayerCharacter*, Character);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeginFocus, ADFDPlayerCharacter*, Character);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEndFocus, ADFDPlayerCharacter*, Character);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteract, ADFDPlayerCharacter*, Character);
/*-----------------------------------------*/


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DEATHFROMDARKNESS_API UDFDInteractionComponent : public UWidgetComponent
{
	GENERATED_BODY()

/*-----------------------------------------------------PROTECTED------------------------------------------------------*/
protected:
	virtual void Deactivate() override;

	bool CanInteract(ADFDPlayerCharacter* Character) const;

	UPROPERTY()
	TArray<ADFDPlayerCharacter*> InterActors;

/*-------------------------------------------------------PUBLIC-------------------------------------------------------*/
public:
	UDFDInteractionComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction")
	float InteractionTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction")
	float InteractionDistance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	bool bAllowMultipleInterActors;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction")
	FText InteractionNameText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction")
	FText InteractionActionText;
	
	
	UPROPERTY(EditAnywhere, BlueprintAssignable)
	FOnBeginInteract OnBeginInteract;

	UPROPERTY(EditAnywhere, BlueprintAssignable)
	FOnEndInteract OnEndInteract;

	UPROPERTY(EditAnywhere, BlueprintAssignable)
	FOnBeginFocus OnBeginFocus;

	UPROPERTY(EditAnywhere, BlueprintAssignable)
	FOnEndFocus OnEndFocus;

	UPROPERTY(EditAnywhere, BlueprintAssignable)
	FOnInteract OnInteract;

	void RefreshWidget();

	void BeginFocus(ADFDPlayerCharacter* Character);
	void EndFocus(ADFDPlayerCharacter* Character);

	void BeginInteract(ADFDPlayerCharacter* Character);
	void EndInteract(ADFDPlayerCharacter* Character);

	void Interact(ADFDPlayerCharacter* Character);
	

	UFUNCTION(BlueprintPure, Category="Interaction")
	float GetInteractPercentage();

	UFUNCTION(BlueprintCallable, Category="Interaction")
	void SetInteractableNameText(const FText& NewNameText);

	UFUNCTION(BlueprintCallable, Category="Interaction")
	void SetInteractableActionText(const FText& NewActionText);

/*-------------------------------------------------------PRIVATE------------------------------------------------------*/
private:
	void PrimitiveRenderFunc(bool bRenderCustom);
};
