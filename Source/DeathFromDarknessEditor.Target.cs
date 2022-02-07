// Death From Darkness. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class DeathFromDarknessEditorTarget : TargetRules
{
	public DeathFromDarknessEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "DeathFromDarkness" } );
	}
}
