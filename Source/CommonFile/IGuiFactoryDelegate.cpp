#include "IGuiFactoryDelegate.h"

namespace Gui
{
    IGuiFactoryDelegate::IGuiFactoryDelegate()
    {
        m_nId = 0;
    }

    uint8_t IGuiFactoryDelegate::GetHeaderOfHandle()
    {
        if (m_nId == 0)
        {
            m_nId = m_pObjectFactory->GenerateNewFactoryId();
        }
        return m_nId;
    }

    IRefObject* IGuiFactoryDelegate::Create(Gui::INode* pNode)
    {

    }

    // Invoke method
    void IGuiFactoryDelegate::Invoke(IRefObject* pObj, CString strMethod)
    {

    }

    void IGuiFactoryDelegate::Invoke(IRefObject* pObj, CString strMethod, IRefObjectParams* pParams)
    {

    }

    void IGuiFactoryDelegate::Invoke(IRefObject* pObj, CString strMethod, IRefObjectParams* pParams, IRefObjectCallback* pCallback)
    {

    }
}