using UnrealBuildTool;

public class BullCowGame : ModuleRules
{
	public BullCowGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Slate" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
