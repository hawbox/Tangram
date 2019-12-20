#include "stdafx.h"
#include "dllmain.h"
#include "WizForm.h"
#include "tangramobj.h"

namespace TangramCLR {
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
}
