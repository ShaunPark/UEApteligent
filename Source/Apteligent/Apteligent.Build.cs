// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using System.IO;

namespace UnrealBuildTool.Rules
{

    public class Apteligent : ModuleRules
    {
        public Apteligent(TargetInfo Target)
        {

            PublicIncludePaths.AddRange(
                new string[] {
                "Apteligent/Public"
                    // ... add public include paths required here ...
                }
                );


            PrivateIncludePaths.AddRange(
                new string[] {
                "Apteligent/Private",
                    // ... add other private include paths required here ...
                }
                );


            PublicDependencyModuleNames.AddRange(
                new string[]
                {
                "Core",
                "CoreUObject",
                "Engine"

                    // ... add other public dependencies that you statically link with here ...
                }
                );


            PrivateDependencyModuleNames.AddRange(
                new string[]
                {
                    // ... add private dependencies that you statically link with here ...	
                }
                );


            DynamicallyLoadedModuleNames.AddRange(
                new string[]
                {
                    // ... add any modules that your module loads dynamically here ...
                }
                );

            if (Target.Platform == UnrealTargetPlatform.IOS)
            {
                PublicFrameworks.AddRange(
                    new string[] {
                        "SystemConfiguration"
                    }
                );

                var LibDir = Path.Combine(ModuleDirectory, "..", "..", "lib", "iOS");
                PrivateIncludePaths.Add(LibDir);

                var Lib = Path.Combine(LibDir, "libCrittercism_v5_5_6.a");
                PublicAdditionalLibraries.Add(Lib);
            }
            else if (Target.Platform == UnrealTargetPlatform.Android)
            {
                PrivateDependencyModuleNames.AddRange(  new string[] {"Launch"});
                string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, BuildConfiguration.RelativeEnginePath);
                AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", Path.Combine(PluginPath, "Apteligent_APL.xml")));
            }
        }
    }
}
