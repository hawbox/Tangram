#pragma once

#include "IRefObject.h"
#include "IGui.h"

using namespace RefObject;

namespace Gui
{
    class IGuiFactoryDelegate : public IFactoryDelegate
    {
    public:
        IGuiFactoryDelegate();
        virtual ~IGuiFactoryDelegate() {};

        uint8_t GetHeaderOfHandle() override;
        IRefObject* Create(Gui::INode* pNode) override;

        // Invoke method
        void Invoke(IRefObject* pObj, CString strMethod) override;
        void Invoke(IRefObject* pObj, CString strMethod, IRefObjectParams* pParams) override;
        void Invoke(IRefObject* pObj, CString strMethod, IRefObjectParams* pParams, IRefObjectCallback* pCallback) override;
    protected:
        uint8_t m_nId;
    };
}
