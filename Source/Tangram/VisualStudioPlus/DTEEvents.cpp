/********************************************************************************
*					Tangram Library - version 10.0.0							*
*********************************************************************************
* Copyright (C) 2002-2020 by Tangram Team.   All Rights Reserved.				*
*
* THIS SOURCE FILE IS THE PROPERTY OF TANGRAM TEAM AND IS NOT TO
* BE RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED
* WRITTEN CONSENT OF TANGRAM TEAM.
*
* THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS
* OUTLINED IN THE TANGRAM LICENSE AGREEMENT.TANGRAM TEAM
* GRANTS TO YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE
* THIS SOFTWARE ON A SINGLE COMPUTER.
*
* CONTACT INFORMATION:
* mailto:tangramteam@outlook.com
* https://www.tangram.dev
*
********************************************************************************/
#include "../StdAfx.h"
#include "DTEEvent.h"
namespace VisualStudioPlus
{
	namespace VSEvents
	{
		_ATL_FUNC_INFO BuildBegin = { CC_STDCALL,VT_EMPTY,2,VT_I4,VT_I4 };
		_ATL_FUNC_INFO BuildDone = { CC_STDCALL,VT_EMPTY,2,VT_I4,VT_I4 };
		_ATL_FUNC_INFO BuildProjConfigBegin = { CC_STDCALL,VT_EMPTY,4,VT_BSTR,VT_BSTR,VT_BSTR,VT_BSTR };
		_ATL_FUNC_INFO BuildProjConfigDone = { CC_STDCALL,VT_EMPTY,5,VT_BSTR,VT_BSTR,VT_BSTR,VT_BSTR,VT_BOOL };

		_ATL_FUNC_INFO Click = { CC_STDCALL,VT_EMPTY,3,VT_DISPATCH,VT_BOOL | VT_BYREF,VT_BOOL | VT_BYREF };

		_ATL_FUNC_INFO BeforeExecute = { CC_STDCALL,VT_EMPTY,5,VT_BSTR,VT_I4,VT_VARIANT,VT_VARIANT,VT_BOOL | VT_BYREF };
		_ATL_FUNC_INFO AfterExecute = { CC_STDCALL,VT_EMPTY,4,VT_BSTR,VT_I4,VT_VARIANT,VT_VARIANT };

		_ATL_FUNC_INFO EnterRunMode = { CC_STDCALL,VT_EMPTY,1,VT_I4 };
		_ATL_FUNC_INFO EnterDesignMode = { CC_STDCALL,VT_EMPTY,1,VT_I4 };
		_ATL_FUNC_INFO EnterBreakMode = { CC_STDCALL,VT_EMPTY,2,VT_I4,VT_I4 | VT_BYREF };
		_ATL_FUNC_INFO ExceptionThrown = { CC_STDCALL,VT_EMPTY,5,VT_BSTR,VT_BSTR,VT_I4,VT_BSTR,VT_I4 | VT_BYREF };
		_ATL_FUNC_INFO ExceptionNotHandled = { CC_STDCALL,VT_EMPTY,5,VT_BSTR,VT_BSTR,VT_I4,VT_BSTR,VT_I4 | VT_BYREF };
		_ATL_FUNC_INFO ContextChanged = { CC_STDCALL,VT_EMPTY,4,VT_I4 | VT_BYREF,VT_I4 | VT_BYREF,VT_I4 | VT_BYREF,VT_I4 | VT_BYREF };

		_ATL_FUNC_INFO DocumentSaved = { CC_STDCALL,VT_EMPTY,1,VT_I4 | VT_BYREF };
		_ATL_FUNC_INFO DocumentClosing = { CC_STDCALL,VT_EMPTY,1,VT_I4 | VT_BYREF };
		_ATL_FUNC_INFO DocumentOpening = { CC_STDCALL,VT_EMPTY,2,VT_BSTR,VT_BOOL };
		_ATL_FUNC_INFO DocumentOpened = { CC_STDCALL,VT_EMPTY,1,VT_I4 | VT_BYREF };

		_ATL_FUNC_INFO StartupComplete = { CC_STDCALL,VT_EMPTY,0,NULL };
		_ATL_FUNC_INFO BeginShutdown = { CC_STDCALL,VT_EMPTY,0,NULL };
		_ATL_FUNC_INFO ModeChanged = { CC_STDCALL,VT_EMPTY,1,VT_I4 };
		_ATL_FUNC_INFO MacrosRuntimeReset = { CC_STDCALL,VT_EMPTY,0,NULL };

		_ATL_FUNC_INFO FindDoneType = { CC_STDCALL,VT_EMPTY,2,VT_I4,VT_BOOL };

		_ATL_FUNC_INFO PaneAdded = { CC_STDCALL,VT_EMPTY,1,VT_I4 | VT_BYREF };
		_ATL_FUNC_INFO PaneUpdated = { CC_STDCALL,VT_EMPTY,1,VT_I4 | VT_BYREF };
		_ATL_FUNC_INFO PaneClearing = { CC_STDCALL,VT_EMPTY,1,VT_I4 | VT_BYREF };

		_ATL_FUNC_INFO ItemAdded = { CC_STDCALL,VT_EMPTY,1,VT_I4 | VT_BYREF };
		_ATL_FUNC_INFO ItemRemoved = { CC_STDCALL,VT_EMPTY,1,VT_I4 | VT_BYREF };
		_ATL_FUNC_INFO ItemRenamed = { CC_STDCALL,VT_EMPTY,2,VT_I4 | VT_BYREF,VT_BSTR };


		_ATL_FUNC_INFO Change = { CC_STDCALL,VT_EMPTY,0,NULL };

		_ATL_FUNC_INFO Opened = { CC_STDCALL,VT_EMPTY,0,NULL };
		_ATL_FUNC_INFO BeforeClosing = { CC_STDCALL,VT_EMPTY,0,NULL };
		_ATL_FUNC_INFO AfterClosing = { CC_STDCALL,VT_EMPTY,0,NULL };
		_ATL_FUNC_INFO QueryCloseSolution = { CC_STDCALL,VT_EMPTY,1,VT_BOOL | VT_BYREF };
		_ATL_FUNC_INFO Renamed = { CC_STDCALL,VT_EMPTY,1,VT_BSTR };
		_ATL_FUNC_INFO ProjectAdded = { CC_STDCALL,VT_EMPTY,1,VT_I4 | VT_BYREF };
		_ATL_FUNC_INFO ProjectRemoved = { CC_STDCALL,VT_EMPTY,1,VT_I4 | VT_BYREF };
		_ATL_FUNC_INFO ProjectRenamed = { CC_STDCALL,VT_EMPTY,2,VT_I4 | VT_BYREF,VT_BSTR };

		_ATL_FUNC_INFO TaskAdded = { CC_STDCALL,VT_EMPTY,1,VT_I4 | VT_BYREF };
		_ATL_FUNC_INFO TaskRemoved = { CC_STDCALL,VT_EMPTY,1,VT_I4 | VT_BYREF };
		_ATL_FUNC_INFO TaskModified = { CC_STDCALL,VT_EMPTY,2,VT_I4 | VT_BYREF,VT_I4 };
		_ATL_FUNC_INFO TaskNavigated = { CC_STDCALL,VT_EMPTY,2,VT_I4 | VT_BYREF,VT_BOOL | VT_BYREF };

		_ATL_FUNC_INFO LineChanged = { CC_STDCALL,VT_EMPTY,3,VT_I4 | VT_BYREF,VT_I4 | VT_BYREF,VT_I4 };

		_ATL_FUNC_INFO WindowClosing = { CC_STDCALL,VT_EMPTY,1,VT_I4 | VT_BYREF };
		_ATL_FUNC_INFO WindowMoved = { CC_STDCALL,VT_EMPTY,5,VT_I4 | VT_BYREF,VT_I4,VT_I4,VT_I4,VT_I4 };
		_ATL_FUNC_INFO WindowActivated = { CC_STDCALL,VT_EMPTY,2,VT_I4 | VT_BYREF,VT_I4 | VT_BYREF };
		_ATL_FUNC_INFO WindowCreated = { CC_STDCALL,VT_EMPTY,1,VT_I4 | VT_BYREF };

		_ATL_FUNC_INFO WindowHiding = { CC_STDCALL,VT_EMPTY,1,VT_I4 | VT_BYREF };
		_ATL_FUNC_INFO WindowShowing = { CC_STDCALL,VT_EMPTY,1,VT_I4 | VT_BYREF };

		_ATL_FUNC_INFO BeforeKeyPress = { CC_STDCALL,VT_EMPTY,4,VT_BSTR, VT_DISPATCH, VT_BOOL , VT_BOOL | VT_BYREF };
		_ATL_FUNC_INFO AfterKeyPress = { CC_STDCALL,VT_EMPTY,3,VT_BSTR, VT_DISPATCH, VT_BOOL};

		_ATL_FUNC_INFO ElementAdded = { CC_STDCALL,VT_EMPTY,1, VT_DISPATCH};
		_ATL_FUNC_INFO ElementChanged = { CC_STDCALL,VT_EMPTY,2,VT_DISPATCH, VT_I2};
		_ATL_FUNC_INFO ElementDeleted = { CC_STDCALL,VT_EMPTY,2,VT_DISPATCH, VT_DISPATCH};
	}
}
