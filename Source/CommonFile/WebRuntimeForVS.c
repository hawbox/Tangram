

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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

MIDL_DEFINE_GUID(IID, IID_IWebRuntimeCtrl,0x424ec3e0,0x2d0c,0x4b90,0xa1,0xe2,0x16,0x2c,0xc7,0xaa,0xb4,0xbd);


MIDL_DEFINE_GUID(IID, IID_IChromForVSAppObj,0x82249965,0x9d73,0x42d0,0x81,0xcd,0x14,0x99,0x24,0xf4,0x37,0xbb);


MIDL_DEFINE_GUID(IID, LIBID_WebRuntimeForVS,0x4e0ce9e8,0xcba3,0x48d4,0x8a,0xf2,0x54,0x8b,0xf8,0x52,0x36,0xe7);


MIDL_DEFINE_GUID(IID, DIID_IWebRuntimeForVS,0x5199b64b,0x46b9,0x444b,0x8e,0x33,0xb3,0x9a,0xb1,0x93,0xeb,0x55);


MIDL_DEFINE_GUID(CLSID, CLSID_CWebRuntimeForVSDoc,0x4e77a03b,0x254d,0x4956,0x90,0xd8,0xa1,0x5b,0xe8,0x4b,0xbc,0xb8);


MIDL_DEFINE_GUID(IID, DIID__IWebRuntimeCtrlEvents,0x74cb9a2d,0x97fe,0x4e9f,0x8b,0x57,0x95,0x5f,0xba,0x5b,0xf5,0xe3);


MIDL_DEFINE_GUID(CLSID, CLSID_WebRuntimeCtrl,0x635a281c,0xbd31,0x4cf2,0xb3,0x7b,0x9b,0xe9,0xc3,0xd7,0xbe,0x57);


MIDL_DEFINE_GUID(IID, DIID__IChromForVSAppObjEvents,0x37fed054,0x75d7,0x4563,0x85,0x18,0x86,0xb6,0x32,0xe7,0x85,0x63);


MIDL_DEFINE_GUID(CLSID, CLSID_ChromForVSAppObj,0x52f412eb,0x30f0,0x4e90,0x85,0xd3,0x6c,0x3c,0x62,0x1f,0x6b,0xe6);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



