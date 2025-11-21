// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TagGamePrototype : ModuleRules
{
	public TagGamePrototype(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
