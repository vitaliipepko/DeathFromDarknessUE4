// Death From Darkness. All Rights Reserved.


#include "Framework/DFDGameModeBase.h"
#include "Player/DFDPlayerCharacter.h"
#include "Player/DFDPlayerController.h"

ADFDGameModeBase::ADFDGameModeBase()
{
	DefaultPawnClass = ADFDPlayerCharacter::StaticClass();
	PlayerControllerClass = ADFDPlayerController::StaticClass();
}