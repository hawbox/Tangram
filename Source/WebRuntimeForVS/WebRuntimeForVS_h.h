

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for WebRuntimeForVS.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0622 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __WebRuntimeForVS_h_h__
#define __WebRuntimeForVS_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IWebRuntimeCtrl_FWD_DEFINED__
#define __IWebRuntimeCtrl_FWD_DEFINED__
typedef interface IWebRuntimeCtrl IWebRuntimeCtrl;

#endif 	/* __IWebRuntimeCtrl_FWD_DEFINED__ */


#ifndef __IChromForVSAppObj_FWD_DEFINED__
#define __IChromForVSAppObj_FWD_DEFINED__
typedef interface IChromForVSAppObj IChromForVSAppObj;

#endif 	/* __IChromForVSAppObj_FWD_DEFINED__ */


#ifndef __IWebRuntimeForVS_FWD_DEFINED__
#define __IWebRuntimeForVS_FWD_DEFINED__
typedef interface IWebRuntimeForVS IWebRuntimeForVS;

#endif 	/* __IWebRuntimeForVS_FWD_DEFINED__ */


#ifndef __CWebRuntimeForVSDoc_FWD_DEFINED__
#define __CWebRuntimeForVSDoc_FWD_DEFINED__

#ifdef __cplusplus
typedef class CWebRuntimeForVSDoc CWebRuntimeForVSDoc;
#else
typedef struct CWebRuntimeForVSDoc CWebRuntimeForVSDoc;
#endif /* __cplusplus */

#endif 	/* __CWebRuntimeForVSDoc_FWD_DEFINED__ */


#ifndef ___IWebRuntimeCtrlEvents_FWD_DEFINED__
#define ___IWebRuntimeCtrlEvents_FWD_DEFINED__
typedef interface _IWebRuntimeCtrlEvents _IWebRuntimeCtrlEvents;

#endif 	/* ___IWebRuntimeCtrlEvents_FWD_DEFINED__ */


#ifndef __WebRuntimeCtrl_FWD_DEFINED__
#define __WebRuntimeCtrl_FWD_DEFINED__

#ifdef __cplusplus
typedef class WebRuntimeCtrl WebRuntimeCtrl;
#else
typedef struct WebRuntimeCtrl WebRuntimeCtrl;
#endif /* __cplusplus */

#endif 	/* __WebRuntimeCtrl_FWD_DEFINED__ */


#ifndef ___IChromForVSAppObjEvents_FWD_DEFINED__
#define ___IChromForVSAppObjEvents_FWD_DEFINED__
typedef interface _IChromForVSAppObjEvents _IChromForVSAppObjEvents;

#endif 	/* ___IChromForVSAppObjEvents_FWD_DEFINED__ */


#ifndef __ChromForVSAppObj_FWD_DEFINED__
#define __ChromForVSAppObj_FWD_DEFINED__

#ifdef __cplusplus
typedef class ChromForVSAppObj ChromForVSAppObj;
#else
typedef struct ChromForVSAppObj ChromForVSAppObj;
#endif /* __cplusplus */

#endif 	/* __ChromForVSAppObj_FWD_DEFINED__ */


/* header files for imported files */
#include "ocidl.h"
#include "tangram.h"
#include "shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IWebRuntimeCtrl_INTERFACE_DEFINED__
#define __IWebRuntimeCtrl_INTERFACE_DEFINED__

/* interface IWebRuntimeCtrl */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWebRuntimeCtrl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("424ec3e0-2d0c-4b90-a1e2-162cc7aab4bd")
    IWebRuntimeCtrl : public IDispatch
    {
    public:
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_HWND( 
            /* [retval][out] */ LONG_PTR *pHWND) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IWebRuntimeCtrlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWebRuntimeCtrl * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWebRuntimeCtrl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWebRuntimeCtrl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWebRuntimeCtrl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWebRuntimeCtrl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWebRuntimeCtrl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWebRuntimeCtrl * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HWND )( 
            IWebRuntimeCtrl * This,
            /* [retval][out] */ LONG_PTR *pHWND);
        
        END_INTERFACE
    } IWebRuntimeCtrlVtbl;

    interface IWebRuntimeCtrl
    {
        CONST_VTBL struct IWebRuntimeCtrlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWebRuntimeCtrl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWebRuntimeCtrl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWebRuntimeCtrl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWebRuntimeCtrl_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWebRuntimeCtrl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWebRuntimeCtrl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWebRuntimeCtrl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWebRuntimeCtrl_get_HWND(This,pHWND)	\
    ( (This)->lpVtbl -> get_HWND(This,pHWND) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWebRuntimeCtrl_INTERFACE_DEFINED__ */


#ifndef __IChromForVSAppObj_INTERFACE_DEFINED__
#define __IChromForVSAppObj_INTERFACE_DEFINED__

/* interface IChromForVSAppObj */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IChromForVSAppObj;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("82249965-9d73-42d0-81cd-149924f437bb")
    IChromForVSAppObj : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateBrowser( 
            ULONGLONG hParentWnd,
            BSTR strUrls,
            /* [out] */ IChromeWebBrowser **ppRet) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetCreatingBrowserWnd( 
            LONGLONG *retHandle) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IChromForVSAppObjVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IChromForVSAppObj * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IChromForVSAppObj * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IChromForVSAppObj * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IChromForVSAppObj * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IChromForVSAppObj * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IChromForVSAppObj * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IChromForVSAppObj * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateBrowser )( 
            IChromForVSAppObj * This,
            ULONGLONG hParentWnd,
            BSTR strUrls,
            /* [out] */ IChromeWebBrowser **ppRet);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetCreatingBrowserWnd )( 
            IChromForVSAppObj * This,
            LONGLONG *retHandle);
        
        END_INTERFACE
    } IChromForVSAppObjVtbl;

    interface IChromForVSAppObj
    {
        CONST_VTBL struct IChromForVSAppObjVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IChromForVSAppObj_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IChromForVSAppObj_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IChromForVSAppObj_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IChromForVSAppObj_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IChromForVSAppObj_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IChromForVSAppObj_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IChromForVSAppObj_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IChromForVSAppObj_CreateBrowser(This,hParentWnd,strUrls,ppRet)	\
    ( (This)->lpVtbl -> CreateBrowser(This,hParentWnd,strUrls,ppRet) ) 

#define IChromForVSAppObj_GetCreatingBrowserWnd(This,retHandle)	\
    ( (This)->lpVtbl -> GetCreatingBrowserWnd(This,retHandle) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IChromForVSAppObj_INTERFACE_DEFINED__ */



#ifndef __WebRuntimeForVS_LIBRARY_DEFINED__
#define __WebRuntimeForVS_LIBRARY_DEFINED__

/* library WebRuntimeForVS */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_WebRuntimeForVS;

#ifndef __IWebRuntimeForVS_DISPINTERFACE_DEFINED__
#define __IWebRuntimeForVS_DISPINTERFACE_DEFINED__

/* dispinterface IWebRuntimeForVS */
/* [uuid] */ 


EXTERN_C const IID DIID_IWebRuntimeForVS;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("5199b64b-46b9-444b-8e33-b39ab193eb55")
    IWebRuntimeForVS : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IWebRuntimeForVSVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWebRuntimeForVS * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWebRuntimeForVS * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWebRuntimeForVS * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWebRuntimeForVS * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWebRuntimeForVS * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWebRuntimeForVS * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWebRuntimeForVS * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IWebRuntimeForVSVtbl;

    interface IWebRuntimeForVS
    {
        CONST_VTBL struct IWebRuntimeForVSVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWebRuntimeForVS_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWebRuntimeForVS_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWebRuntimeForVS_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWebRuntimeForVS_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWebRuntimeForVS_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWebRuntimeForVS_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWebRuntimeForVS_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IWebRuntimeForVS_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CWebRuntimeForVSDoc;

#ifdef __cplusplus

class DECLSPEC_UUID("4e77a03b-254d-4956-90d8-a15be84bbcb8")
CWebRuntimeForVSDoc;
#endif

#ifndef ___IWebRuntimeCtrlEvents_DISPINTERFACE_DEFINED__
#define ___IWebRuntimeCtrlEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IWebRuntimeCtrlEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__IWebRuntimeCtrlEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("74cb9a2d-97fe-4e9f-8b57-955fba5bf5e3")
    _IWebRuntimeCtrlEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IWebRuntimeCtrlEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IWebRuntimeCtrlEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IWebRuntimeCtrlEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IWebRuntimeCtrlEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IWebRuntimeCtrlEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IWebRuntimeCtrlEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IWebRuntimeCtrlEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IWebRuntimeCtrlEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _IWebRuntimeCtrlEventsVtbl;

    interface _IWebRuntimeCtrlEvents
    {
        CONST_VTBL struct _IWebRuntimeCtrlEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IWebRuntimeCtrlEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IWebRuntimeCtrlEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IWebRuntimeCtrlEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IWebRuntimeCtrlEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IWebRuntimeCtrlEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IWebRuntimeCtrlEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IWebRuntimeCtrlEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IWebRuntimeCtrlEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_WebRuntimeCtrl;

#ifdef __cplusplus

class DECLSPEC_UUID("635a281c-bd31-4cf2-b37b-9be9c3d7be57")
WebRuntimeCtrl;
#endif

#ifndef ___IChromForVSAppObjEvents_DISPINTERFACE_DEFINED__
#define ___IChromForVSAppObjEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IChromForVSAppObjEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__IChromForVSAppObjEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("37fed054-75d7-4563-8518-86b632e78563")
    _IChromForVSAppObjEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IChromForVSAppObjEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IChromForVSAppObjEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IChromForVSAppObjEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IChromForVSAppObjEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IChromForVSAppObjEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IChromForVSAppObjEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IChromForVSAppObjEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IChromForVSAppObjEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _IChromForVSAppObjEventsVtbl;

    interface _IChromForVSAppObjEvents
    {
        CONST_VTBL struct _IChromForVSAppObjEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IChromForVSAppObjEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IChromForVSAppObjEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IChromForVSAppObjEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IChromForVSAppObjEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IChromForVSAppObjEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IChromForVSAppObjEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IChromForVSAppObjEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IChromForVSAppObjEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_ChromForVSAppObj;

#ifdef __cplusplus

class DECLSPEC_UUID("52f412eb-30f0-4e90-85d3-6c3c621f6be6")
ChromForVSAppObj;
#endif
#endif /* __WebRuntimeForVS_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  BSTR_UserSize64(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal64(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal64(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree64(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


