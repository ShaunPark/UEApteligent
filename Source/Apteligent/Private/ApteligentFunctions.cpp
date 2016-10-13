//
//  Created by Shaun Park on 2016-10-05.
//
#include "ApteligentPrivatePCH.h"
#include "Android/AndroidApplication.h"
#include <android/log.h>
#if PLATFORM_ANDROID
#include "AndroidJNI.h"
#define APTELIGENT_CLASS "com/crittercism/app/Crittercism"
#define GAME_ACTIVITY_CLASS "com/epicgames/ue4/GameActivity"

#endif


#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "Apteligent"


#if PLATFORM_IOS
NSArray* GetNSStringArray(TArray<FString> FStringArray)
{
	NSMutableArray* NewArray = [NSMutableArray array];

	for (auto Itr(FStringArray.CreateIterator()); Itr; Itr++)
	{
		FString String = (*Itr);
		[NewArray addObject : String.GetNSString()];
	}

	return NewArray;
}
#endif

bool ValidateParams(FString Function, FString Event, TArray<FString> ParamKeys, TArray<FString> ParamValues)
{
	if (ParamKeys.Num() != ParamValues.Num())
	{
		UE_LOG(LogApteligent, Error, TEXT("%s failed for event %s because number of param keys (%i) differs from number of param values (%i)"), *Function, *Event, ParamKeys.Num(), ParamValues.Num());
		return false;
	}

	if (ParamKeys.Num() > 10)
	{
		UE_LOG(LogApteligent, Error, TEXT("%s failed for event %s because the number of keys (%i) can not be greater than 10"), *Function, *Event, ParamKeys.Num());
		return false;
	}

	if (ParamValues.Num() > 10)
	{
		UE_LOG(LogApteligent, Error, TEXT("%s failed for event %s because the number of values (%i) can not be greater than 10"), *Function, *Event, ParamValues.Num());
		return false;
	}

	return true;
}

void UApteligentFunctions::Crittercism_EnableWithAppID(FString appId)
{
#if PLATFORM_IOS
		[Crittercism enableWithAppID : appId.GetNSString()];
#elif PLATFORM_ANDROID
	JNIEnv* env = FAndroidApplication::GetJavaEnv();
	jclass jaClass = FAndroidApplication::FindJavaClass(GAME_ACTIVITY_CLASS);

	if (jaClass) {
		jobject jaObject = FAndroidApplication::GetGameActivityThis();

		jmethodID jcMethod = env->GetMethodID(jaClass, "getApplicationContext", "()Landroid/content/Context;");
		if (jcMethod) {

			jobject jcObject = env->CallObjectMethod(jaObject, jcMethod);
			jclass jClass = FAndroidApplication::FindJavaClass(APTELIGENT_CLASS);
			jmethodID jMethod = env->GetStaticMethodID(jClass, "initialize", "(Landroid/content/Context;Ljava/lang/String;)V");
			
			const char* aId = TCHAR_TO_ANSI(*appId);
			jstring jAppId = env->NewStringUTF(aId);

			env->CallStaticVoidMethod(jClass, jMethod, jcObject, jAppId);
		}
		else {
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Faild to find method %s", "getApplicationContext");
		}
	}
	else {
		__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Faild to find class %s", GAME_ACTIVITY_CLASS);
	}

#endif
}

void UApteligentFunctions::Crittercism_LogHandledException(FString name, FString reason)
{
#if PLATFORM_IOS
	[Crittercism logHandledException : [NSException exceptionWithName:name.GetNSString() reason:reason.GetNSString() userInfo:nil]];
#endif
}

void UApteligentFunctions::Crittercism_LogNetworkRequest(FString method,
																												 FString uriString,
																												 int latency,
																												 int bytesRead,
																												 int bytesSent,
																												 int responseCode,
																												 int errorCode)
{
#if PLATFORM_IOS
		NSError *error = nil;
		if ( errorCode != 0 ) {
			error = [[NSError alloc] initWithDomain:uriString.GetNSString()	code:errorCode userInfo:nil];
		}
		[Crittercism logNetworkRequest : method.GetNSString()
												urlString:uriString.GetNSString()
												latency:latency
												bytesRead:bytesRead
												bytesSent:bytesSent
												responseCode:responseCode
												error:error];
#endif
}

void UApteligentFunctions::Crittercism_LeaveBreadcrumb(FString breadcrumb)
{
#if PLATFORM_IOS
	[Crittercism leaveBreadcrumb : breadcrumb.GetNSString()];
#elif PLATFORM_ANDROID
	JNIEnv* env = FAndroidApplication::GetJavaEnv();
	jclass jClass = FAndroidApplication::FindJavaClass(APTELIGENT_CLASS);

	if (jClass) {

		jmethodID jMethod = env->GetStaticMethodID(jClass, "leaveBreadcrumb", "(Ljava/lang/String;)V");

		if (jMethod) {
			const char* bc = TCHAR_TO_ANSI(*breadcrumb);
			jstring jbc = env->NewStringUTF(bc);

			env->CallStaticVoidMethod(jClass, jMethod, jbc);
		}
		else {
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Faild to find method %s", "leaveBreadcrumb");
		}
	}
	else {
		__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Faild to find class %s", APTELIGENT_CLASS);
	}
#endif
}

void UApteligentFunctions::Crittercism_SetUsername(FString name)
{
#if PLATFORM_IOS
	[Crittercism setUsername : name.GetNSString()];
#elif PLATFORM_ANDROID
	JNIEnv* env = FAndroidApplication::GetJavaEnv();
	jclass jClass = FAndroidApplication::FindJavaClass(APTELIGENT_CLASS);

	if (jClass) {

		jmethodID jMethod = env->GetStaticMethodID(jClass, "setUsername", "(Ljava/lang/String;)V");

		if (jMethod) {
			const char* bc = TCHAR_TO_ANSI(*name);
			jstring jbc = env->NewStringUTF(bc);

			env->CallStaticVoidMethod(jClass, jMethod, jbc);
		}
		else {
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Faild to find method %s", "setUsername");
		}
	}
	else {
		__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Faild to find class %s", APTELIGENT_CLASS);
	}
#endif
}

#if PLATFORM_IOS
void UApteligentFunctions::Crittercism_SetValue(FString name, FString value)
{
	[Crittercism setValue : value.GetNSString() forKey : name.GetNSString()];
}
#endif

void UApteligentFunctions::Crittercism_SetOptOutStatus(bool status)
{
#if PLATFORM_IOS
	[Crittercism setOptOutStatus : status];
#endif
}

void UApteligentFunctions::Crittercism_BeginUserflow(FString name)
{
#if PLATFORM_IOS
	[Crittercism beginUserflow : name.GetNSString()];
#elif PLATFORM_ANDROID
	JNIEnv* env = FAndroidApplication::GetJavaEnv();
	jclass jClass = FAndroidApplication::FindJavaClass(APTELIGENT_CLASS);

	if (jClass) {

		jmethodID jMethod = env->GetStaticMethodID(jClass, "beginUserflow", "(Ljava/lang/String;)V");

		if (jMethod) {
			const char* bc = TCHAR_TO_ANSI(*name);
			jstring jbc = env->NewStringUTF(bc);

			env->CallStaticVoidMethod(jClass, jMethod, jbc);
		}
		else {
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Faild to find method %s", "beginUserflow");
		}
	}
	else {
		__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Faild to find class %s", APTELIGENT_CLASS);
	}
#endif
}

void UApteligentFunctions::Crittercism_BeginUserflowWithValue(FString name, int value)
{
#if PLATFORM_IOS
	[Crittercism beginUserflow : name.GetNSString() withValue:value];
#elif PLATFORM_ANDROID
	JNIEnv* env = FAndroidApplication::GetJavaEnv();
	jclass jClass = FAndroidApplication::FindJavaClass(APTELIGENT_CLASS);

	if (jClass) {

		jmethodID jMethod = env->GetStaticMethodID(jClass, "beginUserflow", "(Ljava/lang/String;I)V");

		if (jMethod) {
			const char* bc = TCHAR_TO_ANSI(*name);
			jstring jbc = env->NewStringUTF(bc);

			env->CallStaticVoidMethod(jClass, jMethod, jbc, value);
		}
		else {
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Faild to find method %s", "beginUserflow");
		}
	}
	else {
		__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Faild to find class %s", APTELIGENT_CLASS);
	}
#endif
}

void UApteligentFunctions::Crittercism_EndUserflow(FString name)
{
#if PLATFORM_IOS
	[Crittercism endUserflow : name.GetNSString()];
#elif PLATFORM_ANDROID
	JNIEnv* env = FAndroidApplication::GetJavaEnv();
	jclass jClass = FAndroidApplication::FindJavaClass(APTELIGENT_CLASS);

	if (jClass) {

		jmethodID jMethod = env->GetStaticMethodID(jClass, "endUserflow", "(Ljava/lang/String;)V");

		if (jMethod) {
			const char* bc = TCHAR_TO_ANSI(*name);
			jstring jbc = env->NewStringUTF(bc);

			env->CallStaticVoidMethod(jClass, jMethod, jbc);
		}
		else {
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Faild to find method %s", "endUserflow");
		}
	}
	else {
		__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Faild to find class %s", APTELIGENT_CLASS);
	}
#endif
}

void UApteligentFunctions::Crittercism_FailUserflow(FString name)
{
#if PLATFORM_IOS
	[Crittercism failUserflow : name.GetNSString()];
#elif PLATFORM_ANDROID
	JNIEnv* env = FAndroidApplication::GetJavaEnv();
	jclass jClass = FAndroidApplication::FindJavaClass(APTELIGENT_CLASS);

	if (jClass) {

		jmethodID jMethod = env->GetStaticMethodID(jClass, "failUserflow", "(Ljava/lang/String;)V");

		if (jMethod) {
			const char* bc = TCHAR_TO_ANSI(*name);
			jstring jbc = env->NewStringUTF(bc);

			env->CallStaticVoidMethod(jClass, jMethod, jbc);
		}
		else {
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Faild to find method %s", "failUserflow");
		}
	}
	else {
		__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Faild to find class %s", APTELIGENT_CLASS);
	}
#endif
}

void UApteligentFunctions::Crittercism_CancelUserflow(FString name)
{
#if PLATFORM_IOS
	[Crittercism cancelUserflow : name.GetNSString()];
#elif PLATFORM_ANDROID
	JNIEnv* env = FAndroidApplication::GetJavaEnv();
	jclass jClass = FAndroidApplication::FindJavaClass(APTELIGENT_CLASS);

	if (jClass) {

		jmethodID jMethod = env->GetStaticMethodID(jClass, "cancelUserflow", "(Ljava/lang/String;)V");

		if (jMethod) {
			const char* bc = TCHAR_TO_ANSI(*name);
			jstring jbc = env->NewStringUTF(bc);

			env->CallStaticVoidMethod(jClass, jMethod, jbc);
		}
		else {
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Faild to find method %s", "cancelUserflow");
		}
	}
	else {
		__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Faild to find class %s", APTELIGENT_CLASS);
	}
#endif
}

void UApteligentFunctions::Crittercism_SetUserflowValue(FString name, int value)
{
#if PLATFORM_IOS
	[Crittercism setValue : value forUserflow:name.GetNSString()];
#elif PLATFORM_ANDROID
	JNIEnv* env = FAndroidApplication::GetJavaEnv();
	jclass jClass = FAndroidApplication::FindJavaClass(APTELIGENT_CLASS);

	if (jClass) {

		jmethodID jMethod = env->GetStaticMethodID(jClass, "setUserflowValue", "(Ljava/lang/String;I)V");

		if (jMethod) {
			const char* bc = TCHAR_TO_ANSI(*name);
			jstring jbc = env->NewStringUTF(bc);

			env->CallStaticVoidMethod(jClass, jMethod, jbc, value );
		}
		else {
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Faild to find method %s", "setUserflowValue");
		}
	}
	else {
		__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Faild to find class %s", APTELIGENT_CLASS);
	}
#endif
}

void UApteligentFunctions::Crittercism_GetUserflowValue(FString name)
{
#if PLATFORM_IOS
	[Crittercism valueForUserflow : name.GetNSString()];
#elif PLATFORM_ANDROID
	JNIEnv* env = FAndroidApplication::GetJavaEnv();
	jclass jClass = FAndroidApplication::FindJavaClass(APTELIGENT_CLASS);

	if (jClass) {

		jmethodID jMethod = env->GetStaticMethodID(jClass, "getUserflowValue", "(Ljava/lang/String;)I");

		if (jMethod) {
			const char* bc = TCHAR_TO_ANSI(*name);
			jstring jbc = env->NewStringUTF(bc);

			env->CallStaticVoidMethod(jClass, jMethod, jbc);
		}
		else {
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Faild to find method %s", "getUserflowValue");
		}
	}
	else {
		__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Faild to find class %s", APTELIGENT_CLASS);
	}
#endif
}
