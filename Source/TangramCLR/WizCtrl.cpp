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
			Tangram::WizCtrlDic[this->Handle.ToString()] = this;
			WizForm^ pWizForm = (WizForm^)Tangram::m_pWizForm;
			if (pWizForm != nullptr&&pWizForm->m_pWizListView!=nullptr)
			{
				m_nAppType = pWizForm->m_pWizListView->SelectedItems[0]->Index;
			}
		}
#endif
	}
}
