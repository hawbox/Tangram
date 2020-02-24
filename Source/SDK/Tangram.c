

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for ..\CommonFile\Tangram.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0622 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        EXTERN_C __declspec(selectany) const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif // !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_ITangramExtender,0x19631222,0x1992,0x0612,0x19,0x65,0x06,0x01,0x20,0x16,0x01,0x01);


MIDL_DEFINE_GUID(IID, IID_ITangramDesigner,0x19631222,0x1992,0x0612,0x19,0x65,0x06,0x01,0x20,0x17,0x03,0x21);


MIDL_DEFINE_GUID(IID, IID_IEclipseExtender,0x19631222,0x1992,0x0612,0x19,0x65,0x06,0x01,0x20,0x16,0x09,0x18);


MIDL_DEFINE_GUID(IID, IID_IOfficeExtender,0x19631222,0x1992,0x0612,0x19,0x65,0x06,0x01,0x19,0x63,0x12,0x22);


MIDL_DEFINE_GUID(IID, IID_IVSExtender,0x19631222,0x1992,0x0612,0x19,0x65,0x06,0x01,0x19,0x89,0x07,0x01);


MIDL_DEFINE_GUID(IID, IID_ITangramRestNotify,0x19631222,0x1992,0x0612,0x19,0x65,0x06,0x01,0x20,0x17,0xF7,0xCD);


MIDL_DEFINE_GUID(IID, IID_ITangramRestObj,0x19631222,0x1992,0x0612,0x19,0x65,0x06,0x01,0x20,0x17,0x6C,0x7D);


MIDL_DEFINE_GUID(IID, IID_IVSDocument,0x19631222,0x1992,0x0612,0x19,0x65,0x06,0x01,0x20,0x17,0x08,0x24);


MIDL_DEFINE_GUID(IID, IID_ITaskNotify,0x19631222,0x1992,0x0612,0x19,0x65,0x06,0x01,0x19,0x82,0x22,0xC0);


MIDL_DEFINE_GUID(IID, IID_ITangramTreeNode,0x19631222,0x1992,0x0612,0x19,0x65,0x06,0x01,0x19,0x82,0xC9,0x51);


MIDL_DEFINE_GUID(IID, IID_ITangramTreeViewCallBack,0x19631222,0x1992,0x0612,0x19,0x65,0x06,0x01,0x19,0x82,0x83,0xA6);


MIDL_DEFINE_GUID(IID, IID_ITangramTreeView,0x19631222,0x1992,0x0612,0x19,0x65,0x06,0x01,0x19,0x82,0x83,0xA5);


MIDL_DEFINE_GUID(IID, IID_ITangramApp,0x19631222,0x1992,0x0612,0x19,0x65,0x06,0x01,0x19,0x82,0x00,0x00);


MIDL_DEFINE_GUID(IID, IID_ITangramEventObj,0x19631222,0x1992,0x0612,0x19,0x65,0x06,0x01,0x20,0x16,0x09,0x28);


MIDL_DEFINE_GUID(IID, IID_IWndNode,0x19631222,0x1992,0x0612,0x19,0x65,0x06,0x01,0x19,0x82,0x00,0x04);


MIDL_DEFINE_GUID(IID, IID_IAppExtender,0x19631222,0x1992,0x0612,0x19,0x65,0x06,0x01,0x19,0x82,0x20,0x07);


MIDL_DEFINE_GUID(IID, IID_ITangramEditor,0x19631222,0x1992,0x0612,0x19,0x65,0x06,0x01,0x19,0x82,0x66,0x88);


MIDL_DEFINE_GUID(IID, IID_ITangramDoc,0x19631222,0x1992,0x0612,0x19,0x65,0x06,0x01,0x20,0x16,0x11,0x01);


MIDL_DEFINE_GUID(IID, IID_ITangramDocTemplate,0x19631222,0x1992,0x0612,0x19,0x65,0x06,0x01,0x20,0x17,0x07,0x07);


MIDL_DEFINE_GUID(IID, IID_ITangramJava,0x19631222,0x1992,0x0612,0x19,0x65,0x06,0x01,0xda,0x3b,0x0a,0x66);


MIDL_DEFINE_GUID(IID, IID_ITangram,0x19631222,0x1992,0x0612,0x19,0x65,0x06,0x01,0x19,0x82,0x00,0x01);


MIDL_DEFINE_GUID(IID, IID_ICompositor,0x19631222,0x1992,0x0612,0x19,0x65,0x06,0x01,0x19,0x82,0x00,0x03);


MIDL_DEFINE_GUID(IID, IID_IWndNodeCollection,0x19631222,0x1992,0x0612,0x19,0x65,0x06,0x01,0x19,0x82,0x00,0x17);


MIDL_DEFINE_GUID(IID, IID_ICompositorManager,0x19631222,0x1992,0x0612,0x19,0x65,0x06,0x01,0x19,0x82,0x00,0x02);


MIDL_DEFINE_GUID(IID, IID_IWorkBenchWindow,0x19631222,0x1992,0x0612,0x19,0x65,0x06,0x01,0x19,0x82,0x5D,0x34);


MIDL_DEFINE_GUID(IID, IID_IChromeWebBrowser,0x19631222,0x1992,0x0612,0x19,0x65,0x06,0x01,0x20,0x18,0x08,0x28);


MIDL_DEFINE_GUID(IID, IID_IChromeWebPage,0x19631222,0x1992,0x0612,0x19,0x65,0x06,0x01,0x20,0x18,0x09,0x03);


MIDL_DEFINE_GUID(IID, IID_IOfficeObject,0x19631222,0x1992,0x0612,0x19,0x65,0x06,0x01,0x19,0x65,0x06,0x06);


MIDL_DEFINE_GUID(IID, IID_ITangramCtrl,0x19631222,0x1992,0x0612,0x19,0x65,0x06,0x01,0x19,0x82,0x31,0xDC);


MIDL_DEFINE_GUID(IID, IID_ITangramAppCtrl,0x19631222,0x1992,0x0612,0x19,0x65,0x06,0x01,0x20,0x16,0x10,0x01);


MIDL_DEFINE_GUID(IID, IID_IEclipseCtrl,0x19631222,0x1992,0x0612,0x19,0x65,0x06,0x01,0x20,0x16,0x09,0x12);


MIDL_DEFINE_GUID(IID, LIBID_Tangram,0x19631222,0x1992,0x0612,0x19,0x65,0x06,0x01,0x19,0x82,0x09,0x11);


MIDL_DEFINE_GUID(IID, DIID__ITangram,0x19631222,0x1992,0x0612,0x19,0x65,0x06,0x01,0x19,0x82,0x10,0x02);


MIDL_DEFINE_GUID(CLSID, CLSID_Tangram,0x19631222,0x1992,0x0612,0x19,0x65,0x06,0x01,0x19,0x99,0x06,0x06);


MIDL_DEFINE_GUID(IID, DIID__IWndNodeEvents,0x19631222,0x1992,0x0612,0x19,0x65,0x06,0x01,0x19,0x82,0x10,0x01);


MIDL_DEFINE_GUID(IID, DIID__ITangramObjEvents,0x19631222,0x1992,0x0612,0x19,0x65,0x06,0x01,0x19,0x82,0x19,0x92);


MIDL_DEFINE_GUID(IID, DIID__ITangramAppEvents,0x19631222,0x1992,0x0612,0x19,0x65,0x06,0x01,0x20,0x16,0x09,0x30);


MIDL_DEFINE_GUID(CLSID, CLSID_TangramCtrl,0x19631222,0x1992,0x0612,0x19,0x65,0x06,0x01,0x20,0x07,0x10,0x01);


MIDL_DEFINE_GUID(CLSID, CLSID_TangramJava,0x19631222,0x1992,0x0612,0x19,0x65,0x06,0x01,0x20,0x19,0x03,0x03);


MIDL_DEFINE_GUID(CLSID, CLSID_TangramExtender,0x19631222,0x1992,0x0612,0x19,0x65,0x06,0x01,0x00,0x00,0x00,0x00);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



