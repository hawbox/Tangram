#include "stdafx.h"
#include "dllmain.h"
#include "tangramobj.h"
#include "NavigateCtrl.h"

namespace TangramCLR {

	System::Void NavigateCtrl::LoadNode(TreeNode^ pNode, CTangramXmlParse* pParse)
	{
		if (pParse)
		{
			int nCount = pParse->GetCount();
			for (int i = 0; i < nCount; i++)
			{
				CTangramXmlParse* _pParse = pParse->GetChild(i);
				if (_pParse)
				{
					CString name = _pParse->name();
					if (name == _T("tangramxml"))
					{
						HWND hWnd = (HWND)this->NavigateTreeView->Handle.ToPointer();
						if (hostnode)
						{
							CompositorManager^ pCompositorManager = hostnode->CompositorManager;

							ICompositor* pCompositor = nullptr;
							hostnode->m_pWndNode->get_Compositor(&pCompositor);
							CComBSTR bstrName("");
							pCompositor->get_Name(&bstrName);
							String^ name = pNode->Name + L".";
							name += NavigateTreeView->Name;
							name += L"." + BSTR2STRING(bstrName);
							BSTR strName = STRING2BSTR(name->ToLower());
							Compositor^ _pCompositor = pCompositorManager->CreateCompositor(NavigateTreeView->Handle, name);
							_pCompositor->Open(L"default", BSTR2STRING(_pParse->xml()));
						}
					}
					else
					{
						bool isTreeNode = _pParse->attrBool(_T("treenode"), false);
						if (isTreeNode)
						{
							TreeNode^ pChildNode = pNode->Nodes->Add(BSTR2STRING(_pParse->text()));
							if (pChildNode)
							{
								CString strTagName = name + _T("_tag");
								CTangramXmlParse* pChild2 = pParse->GetChild(strTagName);
								if (pChild2)
								{
									pChildNode->Tag = BSTR2STRING(pChild2->xml());
								}
								LoadNode(pChildNode, pParse->GetChild(i));
							}
						}
					}
				}
			}
		}
	}

	System::Void NavigateCtrl::NavigateCtrl_Load(System::Object^ sender, System::EventArgs^ e) {
		hostnode = TangramCLR::Tangram::CreatingNode;
		CString strXml = _T("");
		if (theApp.m_pTangramImpl)
		{
			strXml = theApp.m_pTangramImpl->m_strNtpDataXml;
		}
		CTangramXmlParse m_Parse;
		if (m_Parse.LoadXml(strXml) || m_Parse.LoadFile(strXml))
		{
			if (this->NavigateTreeView->Nodes->Count == 0)
			{
				LoadNode(NavigateTreeView->Nodes->Add(BSTR2STRING(m_Parse.text())), &m_Parse);
			}
		}
		this->NavigateTreeView->ExpandAll();
	}

	System::Void NavigateCtrl::NavigateTreeView_NodeMouseDoubleClick(System::Object^ sender, System::Windows::Forms::TreeNodeMouseClickEventArgs^ e) {
		if (e->Node->Tag)
		{
			String^ strTag = e->Node->Tag->ToString();
			if (hostnode)
			{
				WndNode^ pHostNode = nullptr;// hostnode->HostNode;
				if (bindnode == nullptr)
				{
					String^ name = hostnode->Attribute[L"bindnode"];
					if (String::IsNullOrEmpty(name) == false)
					{
						WndNodeCollection^ pCol = nullptr;
						hostnode->RootNode->GetNodes(name, bindnode, pCol);
						if (pCol)
						{
							delete pCol;
						}
					}
				}
				if (bindnode != nullptr)
					pHostNode = bindnode;
				if (pHostNode == nullptr)
				{
					pHostNode = hostnode->HostNode;
				}
				if (pHostNode)
				{
					CString strXml = strTag;
					CTangramXmlParse m_Parse;
					if (m_Parse.LoadXml(strXml))
					{
						CString strAction = m_Parse.attr(_T("action"), _T(""));
						if (strAction != _T(""))
						{
							CTangramXmlParse* pChild = m_Parse.GetChild(strAction);
							if (pChild)
							{
								if (strAction == _T("doubleclick"))
									pHostNode->Open(BSTR2STRING(m_Parse.name()), BSTR2STRING(pChild->xml()));
								else if (strAction == _T("openurl"))
								{
									TangramCLR::Tangram::CreateBrowser(System::IntPtr::Zero, BSTR2STRING(pChild->attr(_T("url"), _T("")) + _T("|")));
								}
							}

						}

					}
				}
			}
		}
	}

	System::Void NavigateCtrl::NavigateTreeView_NodeMouseClick(System::Object^ sender, System::Windows::Forms::TreeNodeMouseClickEventArgs^ e) {
	}

	System::Void NavigateCtrl::NavigateTreeView_AfterSelect(System::Object^ sender, System::Windows::Forms::TreeViewEventArgs^ e) {
		if (e->Node->Tag)
		{
			String^ strTag = e->Node->Tag->ToString();
			if (hostnode)
			{
				WndNode^ pHostNode = nullptr; 
				if (bindnode == nullptr)
				{
					String^ name = hostnode->Attribute[L"bindnode"];
					if (String::IsNullOrEmpty(name) == false)
					{
						WndNodeCollection^ pCol = nullptr;
						hostnode->RootNode->GetNodes(name, bindnode, pCol);
						if (pCol)
							delete pCol;
					}
				}
				if (bindnode != nullptr)
					pHostNode = bindnode;
				//WndNode^ 
				if (pHostNode == nullptr)
				{
					pHostNode = hostnode->HostNode;
				}
				if (pHostNode)
				{
					CString strXml = strTag;
					CTangramXmlParse m_Parse;
					if (m_Parse.LoadXml(strXml))
					{
						CTangramXmlParse* pChild = m_Parse.GetChild(_T("afterselected"));
						if (pChild)
							pHostNode->Open(BSTR2STRING(m_Parse.name()), BSTR2STRING(pChild->xml()));
					}
				}
			}
		}
	}
}
