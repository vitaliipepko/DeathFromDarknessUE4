// Death From Darkness. All Rights Reserved.


#include "Widgets/DFDInteractionWidget.h"


void UDFDInteractionWidget::UpdateInteractionWidget(UDFDInteractionComponent* InteractionComponent)
{
	OwningInteractionComponent = InteractionComponent;
	OnUpdateInteractionWidget();
}