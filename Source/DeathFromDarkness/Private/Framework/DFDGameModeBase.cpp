// Death From Darkness. All Rights Reserved.


#include "Framework/DFDGameModeBase.h"
#include "Player/DFDBaseCharacter.h"
#include "Player/DFDPlayerController.h"

ADFDGameModeBase::ADFDGameModeBase()
{
	DefaultPawnClass = ADFDBaseCharacter::StaticClass();
	PlayerControllerClass = ADFDPlayerController::StaticClass();
}