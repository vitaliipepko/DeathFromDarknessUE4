// Death From Darkness. All Rights Reserved.


#include "Components/DFDInteractionComponent.h"
#include "Widgets/DFDInteractionWidget.h"
#include "Player/DFDPlayerCharacter.h"


UDFDInteractionComponent::UDFDInteractionComponent()
{
	UActorComponent::SetComponentTickEnabled(false);

	InteractionTime = 0.f;
	InteractionDistance = 2000.f;
	InteractionNameText = FText::FromString("Interactable Object");
	InteractionActionText = FText::FromString("Interact");
	bAllowMultipleInterActors = true;

	Space = EWidgetSpace::Screen;
	DrawSize = FIntPoint(400, 100);
	bDrawAtDesiredSize = true;

	UActorComponent::SetActive(true);
	SetHiddenInGame(true);
}


void UDFDInteractionComponent::PrimitiveRenderFunc(bool bRenderCustom)
{
	TArray<UPrimitiveComponent*> Primitives;
	GetOwner()->GetComponents<UPrimitiveComponent>(Primitives);

	for(auto &Prim : Primitives)
	{
		Prim->SetRenderCustomDepth(bRenderCustom);
	}
}


void UDFDInteractionComponent::SetInteractableNameText(const FText& NewNameText)
{
	InteractionNameText = NewNameText;
	RefreshWidget();
}


void UDFDInteractionComponent::SetInteractableActionText(const FText& NewActionText)
{
	InteractionActionText = NewActionText;
	RefreshWidget();
}


void UDFDInteractionComponent::Deactivate()
{
	Super::Deactivate();

	for(int32 i = InterActors.Num() - 1; i >= 0; --i)
	{
		if(ADFDPlayerCharacter* InterActor = InterActors[i])
		{
			EndFocus(InterActor);
			EndInteract(InterActor);
		}
	}
	InterActors.Empty();
}


bool UDFDInteractionComponent::CanInteract(ADFDPlayerCharacter* Character) const
{
	const bool bPlayerAlreadyInteracting = !bAllowMultipleInterActors && InterActors.Num() >= 1;
	return !bPlayerAlreadyInteracting && IsActive() && GetOwner() != nullptr && Character != nullptr;
}


void UDFDInteractionComponent::RefreshWidget()
{
	UDFDInteractionWidget* InteractionWidget = Cast<UDFDInteractionWidget>(GetUserWidgetObject());
	if(InteractionWidget)
	{
		InteractionWidget->UpdateInteractionWidget(this);
	}
}


void UDFDInteractionComponent::BeginFocus(ADFDPlayerCharacter* Character)
{
	if(!IsActive() || !GetOwner() || !Character) return;

	OnBeginFocus.Broadcast(Character);
	
	SetHiddenInGame(false);

	PrimitiveRenderFunc(true);

	RefreshWidget();
}


void UDFDInteractionComponent::EndFocus(ADFDPlayerCharacter* Character)
{
	OnEndFocus.Broadcast(Character);
	
	SetHiddenInGame(true);

	PrimitiveRenderFunc(false);
}


void UDFDInteractionComponent::BeginInteract(ADFDPlayerCharacter* Character)
{
	if(!CanInteract(Character)) return;
	
	InterActors.AddUnique(Character);
	OnBeginInteract.Broadcast(Character);
	
}


void UDFDInteractionComponent::EndInteract(ADFDPlayerCharacter* Character)
{
	InterActors.RemoveSingle(Character);
	OnEndInteract.Broadcast(Character);
}


void UDFDInteractionComponent::Interact(ADFDPlayerCharacter* Character)
{
	if(CanInteract(Character))
	{
		OnInteract.Broadcast(Character);
	}
}


float UDFDInteractionComponent::GetInteractPercentage()
{
	if(InterActors.IsValidIndex(0))
	{
		if(ADFDPlayerCharacter* InterActor = InterActors[0])
		{
			if(InterActor && InterActor->IsInteracting())
			{
				return 1.f - FMath::Abs(InterActor->GetRemainingInteractingTime() / InteractionTime);
			}
		}
	}
	return 0.f;
}