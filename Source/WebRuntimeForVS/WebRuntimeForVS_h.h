

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


#ifndef __WebRuntimeCtrl_FWD_DEFINED__
#define __WebRuntimeCtrl_FWD_DEFINED__

#ifdef __cplusplus
typedef class WebRuntimeCtrl WebRuntimeCtrl;
#else
typedef struct WebRuntimeCtrl WebRuntimeCtrl;
#endif /* __cplusplus */

#endif 	/* __WebRuntimeCtrl_FWD_DEFINED__ */


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
#include "shobjidl.h"
#include "tangram.h"

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



#ifndef __WebRuntimeForVS_LIBRARY_DEFINED__
#define __WebRuntimeForVS_LIBRARY_DEFINED__

/* library WebRuntimeForVS */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_WebRuntimeForVS;

EXTERN_C const CLSID CLSID_WebRuntimeCtrl;

#ifdef __cplusplus

class DECLSPEC_UUID("635a281c-bd31-4cf2-b37b-9be9c3d7be57")
WebRuntimeCtrl;
#endif

EXTERN_C const CLSID CLSID_ChromForVSAppObj;

#ifdef __cplusplus

class DECLSPEC_UUID("52f412eb-30f0-4e90-85d3-6c3c621f6be6")
ChromForVSAppObj;
#endif
#endif /* __WebRuntimeForVS_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


