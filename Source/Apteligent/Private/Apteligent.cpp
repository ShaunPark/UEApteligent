// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "ApteligentPrivatePCH.h"

DEFINE_LOG_CATEGORY(LogApteligent);

#define LOCTEXT_NAMESPACE "Apteligent"

class FApteligent : public IApteligent
{
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE(FApteligent, Apteligent)

void FApteligent::StartupModule()
{
}


void FApteligent::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE