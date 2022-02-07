// Death From Darkness. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class DeathFromDarknessTarget : TargetRules
{
	public DeathFromDarknessTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "DeathFromDarkness" } );
	}
}
