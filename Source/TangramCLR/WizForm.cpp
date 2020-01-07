#include "stdafx.h"
#include "dllmain.h"
#include "WizForm.h"
#include "tangramobj.h"

namespace TangramCLR {
	WizForm::WizForm(void)
	{
		InitializeComponent();
		//
		//TODO: Add the constructor code here
		//
#ifndef _WIN64
		TangramCLR::Tangram::m_pWizForm = this;
		TangramCLR::Tangram::WizCtrlDic->Clear();
#endif
	}

	System::Void WizForm::WizForm_Load(System::Object^ sender, System::EventArgs^ e) {
		HWND hWnd = (HWND)this->Handle.ToPointer();
		//::SetWindowLongPtr(hWnd, GWL_STYLE, ::GetWindowLongPtr(hWnd, GWL_STYLE) & ~(WS_SYSMENU));
	}

	void WizForm::NavigateData::set(String^ strData)
	{
		if (String::IsNullOrEmpty(strData)==false)
		{
			theApp.m_pTangramImpl->m_strNtpDataXml = strData;
		}
	}

	void WizForm::InitCustomizeDic(String^ strDicData)
	{
		if (String::IsNullOrEmpty(strDicData)==false)
		{
			CString strData = strDicData;
			int nTokenPos = 0;
			CString strToken = strData.Tokenize(_T("|"), nTokenPos);
			while (!strToken.IsEmpty())
			{
				TangramCLR::Tangram::CustomizeDic[BSTR2STRING(strToken)] = L"";
				strToken = strData.Tokenize(_T("|"), nTokenPos);
			}
		}
	}

	void WizForm::FillListView(String^ _strXmlData, System::Windows::Forms::ListView^ ctrl)
	{
		CString strXmlData = _strXmlData;
		CTangramXmlParse m_Parse;
		ImageList^ pImageList = gcnew ImageList();
		pImageList->ImageSize = System::Drawing::Size(64, 64);
		ctrl->LargeImageList = pImageList;
		int nPos = strXmlData.ReverseFind('\\');
		CString strPath = strXmlData.Left(nPos + 1);
		if (m_Parse.LoadFile(strXmlData) || m_Parse.LoadXml(strXmlData))
		{
			m_pWizListView = ctrl;
			int nCount = m_Parse.GetCount();
			for (int i = 0; i < nCount; i++)
			{
				CTangramXmlParse* pChild = m_Parse.GetChild(i);
				CString _strPath = strPath + pChild->name()+_T(".ico");
				int nIndex = -1;
				if (::PathFileExists(_strPath))
				{
					System::Drawing::Icon^ pIcon = gcnew System::Drawing::Icon(BSTR2STRING(_strPath));
					pImageList->Images->Add(pIcon);
				}
				ctrl->Items->Add(BSTR2STRING(pChild->name()), i)->Tag = BSTR2STRING(pChild->xml());
			}
			if (ctrl->Items->Count > 0)
			{
				ctrl->Items[0]->Selected = true;
			}
		}
	}
}
