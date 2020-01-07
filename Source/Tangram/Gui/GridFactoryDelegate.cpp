#include "../stdafx.h"
#include "GridFactoryDelegate.h"

#include "../Object/RefObject.h"
#include "Grid.h"

namespace Gui
{
    CString GridFactoryDelegate::GetName()
    {
        return L"Grid";
    }

    uint8_t GridFactoryDelegate::GetHeaderOfHandle()
    {
        return 3;
    }

    IRefObject* GridFactoryDelegate::Create(Gui::INode* pNode)
    {
        Grid* pGrid = new Grid();
        int64_t nRow = pNode->GetAttributeAsNumber(_T("row"));
        int64_t nCol = pNode->GetAttributeAsNumber(_T("col"));
        return nullptr;
    }

    void GridFactoryDelegate::Invoke(IRefObject* pObj, CString strMethod)
    {
        if (pObj->GetDelegate() != nullptr)
        {
            pObj->GetDelegate()->Invoke(pObj, strMethod);
        }
    }

    void GridFactoryDelegate::Invoke(IRefObject* pObj, CString strMethod, IRefObjectParams* pParams)
    {
        if (pObj->GetDelegate() != nullptr)
        {
            pObj->GetDelegate()->Invoke(pObj, strMethod, pParams);
        }
    }

    void GridFactoryDelegate::Invoke(IRefObject* pObj, CString strMethod, IRefObjectParams* pParams, IRefObjectCallback* pCallback)
    {
        if (pObj->GetDelegate() != nullptr)
        {
            pObj->GetDelegate()->Invoke(pObj, strMethod, pParams, pCallback);
        }
    }
}