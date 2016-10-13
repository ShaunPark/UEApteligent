//
//  Created by Shaun Park
//

#pragma once

#include "CoreUObject.h"
#include "Engine.h"

#include "IApteligent.h"

// You should place include statements to your module's private header files here.  You only need to
// add includes for headers that are used in most of your module's source files though.

#if PLATFORM_IOS
#import "Crittercism.h"
#endif

DECLARE_LOG_CATEGORY_EXTERN(LogApteligent, Log, All);

#include "ApteligentClasses.h"
