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

#pragma once

#include "../stdafx.h"
#include "../IPC/EndPoint.h"
#include "../Object/RefObjectCallback.h"

class CTangramWinFormWnd;
namespace ChromePlus
{
	class ATL_NO_VTABLE CHtmlWnd :
		public CWindowImpl<CHtmlWnd, CWindow>,
		public CChromeRenderFrameHostProxy,
		public CComObjectRootEx<CComSingleThreadModel>,
		public IDispatchImpl<IChromeWebPage, &_uuidof(IChromeWebPage)>,
		public IPC::EndPoint
	{
	public:
		CHtmlWnd();
		~CHtmlWnd() override;

		BOOL								m_bDevToolWnd;
		bool								m_bWebContentVisible;

		HWND								m_hChildWnd;
		HWND								m_hExtendWnd;
		HWND								m_hWebHostWnd;

		CString								m_strURL;
		CString								m_strCurKey;
		CString								m_strCurXml;
		CString								m_strAppProxyID;

		CCompositor*						m_pCompositor;
		CTangramDoc*						m_pDoc;
		CWndNode*							m_pParentNode;
		CWndNode*							m_pBindNode;
		CTangramWinFormWnd*					m_pBindWinForm;
		ITangramAppProxy*					m_pAppProxy;
		CCompositorManager*					m_pCompositorManager;

		CHtmlWnd*							m_pWebWnd;
		CHtmlWnd*							m_pDevToolWnd;
		map<CString, CString>				m_mapFormsInfo;
		map<CString, CString>				m_mapAtlMFCsInfo;
		map<CString, CString>				m_mapStartupsInfo;
		map<CString, CString>				m_mapeclipsesInfo;
		map<CString, CString>				m_mapWorkBenchInfo;
		map<CString, CString>				m_mapUserControlsInfo;
		map<HWND, CTangramWinFormWnd*>		m_mapWinForm;
		map<HWND, CTangramWinFormWnd*>		m_mapSubWinForm;
		map<CString, CMDIChildFormInfo*>	m_mapChildFormsInfo;

		// IPC callback
		map<CString, ::RefObject::RefObjectCallback*>	m_mapIPCCallback;

		BEGIN_MSG_MAP(CHtmlWnd)
			MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
			MESSAGE_HANDLER(WM_SHOWWINDOW, OnShowWindow)
			MESSAGE_HANDLER(WM_TANGRAMMSG, OnTangramMsg)
			MESSAGE_HANDLER(WM_MOUSEACTIVATE, OnMouseActivate)
			MESSAGE_HANDLER(WM_CHROMEIPCMSG, OnChromeIPCMsgReceived)
			MESSAGE_HANDLER(WM_CHROMEWNDPARENTCHANGED, OnParentChanged)
		END_MSG_MAP()

		BEGIN_COM_MAP(CHtmlWnd)
			COM_INTERFACE_ENTRY(IDispatch)
			COM_INTERFACE_ENTRY(IChromeWebPage)
		END_COM_MAP()

		STDMETHOD(get_HostWnd)(LONGLONG* Val);
		STDMETHOD(put_HostWnd)(LONGLONG newVal);
		STDMETHOD(CreateForm)(BSTR bstrKey, LONGLONG hParent, IDispatch** pRetForm);
		// DOM
		void getElementById(CString strId, ::RefObject::RefObjectCallback* pCallback);

		// IPC message
		IPC::Broker* GetBroker() override;
		void OnIPCMessageReceived(CString strFrom, CString strTo, CString strMsgId, CString strPayload, CString strExtra = NULL) override;

		void SendChromeIPCMessage(CString strId, CString strParam1, CString strParam2, CString strParam3, CString strParam4, CString strParam5);
		CChromeBrowserBase* GetChromeBrowserBase(HWND) override;

		void LoadDocument2Viewport(CString strName, CString strXML);

		CString FindToken(CString pszContent, CString pszDelimiter, int& nStart);

		void HandleChromeIPCMessage(CString strId, CString strParam1, CString strParam2, CString strParam3, CString strParam4, CString strParam5);
		void HandleAggregatedMessage(CString strParam1, CString strParam2);
		void HandleSingleMessage(CString strParam);
		void RenderHTMLElement(CString strRuleName, CString strHTML);
		void RenderHTMLMainWindowElement(CString strHTML);
		void RenderHTMLWebBrowserElement(CString strHTML);
		void RenderHTMLObjectElement(CString strHTML);
		void RenderHTMLExtraElement(CString strHTML);
		void RenderHTMLDataElement(CString strHTML);
		void RenderHTMLDocElement(CString strHTML);
		void OnNTPLoaded();
		void OnWinFormCreated(HWND);
		void OnCloudMsgReceived(CTangramSession*);

	protected:
		ULONG InternalAddRef() { return 1; }
		ULONG InternalRelease() { return 1; }

	private:
		CString m_strDocXml;
		IWndNode* GetParentNode() { return (IWndNode*)m_pParentNode; }
		ICompositor* GetCompositor() { return (ICompositor*)m_pCompositor; }
		void Show(CString strID);
		void OnFinalMessage(HWND hWnd) override;
		LRESULT OnDestroy(UINT, WPARAM, LPARAM, BOOL&);
		LRESULT OnShowWindow(UINT, WPARAM, LPARAM, BOOL&);
		LRESULT OnTangramMsg(UINT, WPARAM, LPARAM, BOOL&);
		LRESULT OnMouseActivate(UINT, WPARAM, LPARAM, BOOL&);
		LRESULT OnParentChanged(UINT, WPARAM, LPARAM, BOOL&);
		LRESULT OnChromeIPCMsgReceived(UINT, WPARAM, LPARAM, BOOL&);
	};
};