//
//  Created by Shaun Park on 2016-10-05.
//

#pragma once

#include "ApteligentFunctions.generated.h"

UCLASS(NotBlueprintable)
class UApteligentFunctions : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (Keywords = "apteligent analytics"), Category = "Apteligent")
		static void Crittercism_EnableWithAppID(FString appId);

	UFUNCTION(BlueprintCallable, meta = (Keywords = "apteligent analytics"), Category = "Apteligent")
		static void Crittercism_LogHandledException(FString name, FString reason);

	UFUNCTION(BlueprintCallable, meta = (Keywords = "apteligent analytics"), Category = "Apteligent")
	static void Crittercism_LogNetworkRequest(FString method,
																						FString uriString,
																						int latency,
																						int bytesRead,
																						int bytesSent,
																						int responseCode,
																						int errorCode);

	UFUNCTION(BlueprintCallable, meta = (Keywords = "apteligent analytics"), Category = "Apteligent")
	static void Crittercism_LeaveBreadcrumb(FString breadcrumb);

	UFUNCTION(BlueprintCallable, meta = (Keywords = "apteligent analytics"), Category = "Apteligent")
	static void Crittercism_SetUsername(FString key);

#if PLATFORM_IOS
	//UFUNCTION(BlueprintCallable, meta = (Keywords = "apteligent analytics"), Category = "Apteligent")
	//static void Crittercism_SetValue(FString value, FString key);
#elif PLATFORM_ANDROID
	//static void Crittercism_SetValue(TMap map);
#endif

	UFUNCTION(BlueprintCallable, meta = (Keywords = "apteligent analytics"), Category = "Apteligent")
	static void Crittercism_SetOptOutStatus(bool status);

	UFUNCTION(BlueprintCallable, meta = (Keywords = "apteligent analytics"), Category = "Apteligent")
	static void Crittercism_BeginUserflow(FString name);

	UFUNCTION(BlueprintCallable, meta = (Keywords = "apteligent analytics"), Category = "Apteligent")
	static void Crittercism_BeginUserflowWithValue(FString name, int value);

	UFUNCTION(BlueprintCallable, meta = (Keywords = "apteligent analytics"), Category = "Apteligent")
	static void Crittercism_EndUserflow(FString name);

	UFUNCTION(BlueprintCallable, meta = (Keywords = "apteligent analytics"), Category = "Apteligent")
	static void Crittercism_FailUserflow(FString name);

	UFUNCTION(BlueprintCallable, meta = (Keywords = "apteligent analytics"), Category = "Apteligent")
	static void Crittercism_CancelUserflow(FString name);

	UFUNCTION(BlueprintCallable, meta = (Keywords = "apteligent analytics"), Category = "Apteligent")
	static void Crittercism_SetUserflowValue(FString name, int value);

	UFUNCTION(BlueprintCallable, meta = (Keywords = "apteligent analytics"), Category = "Apteligent")
	static void Crittercism_GetUserflowValue(FString name);

};
