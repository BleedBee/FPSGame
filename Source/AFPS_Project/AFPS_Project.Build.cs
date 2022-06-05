// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class AFPS_Project : ModuleRules
{
	public AFPS_Project(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		//添加Sqlite数据库路径
		var LibPath = Path.GetFullPath(Path.Combine(ModuleDirectory));
		LibPath += "\\DataBase\\Sqlite\\Libs";
		PublicAdditionalLibraries.Add(Path.Combine(LibPath, "sqlite3.lib"));

		var IncludePath = Path.GetFullPath(Path.Combine(ModuleDirectory));
		IncludePath += "\\DataBase\\Sqlite\\Includes";
		PublicIncludePaths.Add(IncludePath);

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
