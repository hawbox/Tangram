#include "stdafx.h"
#include "dllmain.h"
#include "WizForm.h"

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
}
