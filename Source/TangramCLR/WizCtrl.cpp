#include "stdafx.h"
#include "dllmain.h"
#include "WizCtrl.h"
#include "WizForm.h"
#include "tangramobj.h"

namespace TangramCLR
{
	System::Void WizCtrl::WizCtrl_Load(System::Object^ sender, System::EventArgs^ e) {
#ifndef _WIN64
		hostnode = TangramCLR::Tangram::CreatingNode;
		if (hostnode != nullptr)
		{
			String^ name = hostnode->Name;
			WizForm^ pWizForm = (WizForm^)Tangram::m_pWizForm;
			Tangram::WizCtrlDic[pWizForm->m_pWizListView->SelectedItems[0]->Text] = this;
		}
#endif
	}
}
