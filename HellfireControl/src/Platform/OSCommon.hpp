#pragma once

#include <HellfireControl/Core/Common.hpp>

#ifdef WIN32

#include <Windows.h>

#define STRICT_TYPED_ITEMIDS
#include <shlobj.h>
#include <objbase.h>      
#include <shobjidl.h>     
#include <shlwapi.h> 
#include <propvarutil.h>
#include <propkey.h>      
#include <propidl.h>      
#include <strsafe.h> 
#include <shtypes.h>
#include <new>

#else

#endif