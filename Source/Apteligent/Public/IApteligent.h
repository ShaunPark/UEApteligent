// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ModuleManager.h"

class IApteligent : public IModuleInterface
{
public:

	static inline IApteligent& Get()
	{
		return FModuleManager::LoadModuleChecked< IApteligent >("Apteligent");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("Apteligent");
	}
};