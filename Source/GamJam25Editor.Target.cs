// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class GamJam25EditorTarget : TargetRules
{
	public GamJam25EditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_6;
		ExtraModuleNames.Add("GamJam25");
		
		// ---- Build speed helpers (Editor only) ----
		bUseUnityBuild          = true;   // compiles in chunks
		bUseAdaptiveUnityBuild  = true;   // only de-unify files that change often
		bUsePCHFiles            = true;   // keep a PCH so most headers come precompiled
	}
}
