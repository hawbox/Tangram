#include "../stdafx.h"
#include "Node.h"
#include "../TangramCore.h"

extern CTangram* g_pTangram;

namespace Gui
{
    Node::Node()
    {
        m_nHandle = { 0 };
        m_strTagName = _T("");
        m_strInnerText = _T("");
        m_pParentNode = nullptr;
    }

    CString Node::GetTagName()
    {
        return m_strTagName;
    }

    void Node::SetTagName(CString strTagName)
    {
        m_strTagName = strTagName;
    }

    CString Node::GetText()
    {
        return m_strInnerText;
    }

    void Node::SetText(CString strText)
    {
        m_strInnerText = strText;
    }

    CString Node::GetAttribute(CString strName)
    {
        auto it = m_mapAttributes.find(strName);
        if (it != m_mapAttributes.end())
        {
            return it->second;
        }
        return _T("");
    }

    void Node::SetAttribute(CString strName, CString strValue)
    {
        m_mapAttributes[strName] = strValue;
    }

    int64_t Node::GetAttributeAsNumber(CString strName)
    {
        CString strValue = GetAttribute(strName);
        return _ttoi64(strValue);
    }

    void Node::SetAttribute(CString strName, int64_t nValue)
    {
        WCHAR lpBuffer[256];
        _i64tot_s(nValue, lpBuffer, 256, 10);
        CString strValue(lpBuffer);
        SetAttribute(strName, strValue);
    }

    std::vector<INode*> Node::GetChildNodes()
    {
        return m_vecChildNodes;
    }

    void Node::AddChildNode(INode* pNode)
    {
        m_vecChildNodes.push_back(pNode);
    }

    INode* Node::GetParentNode()
    {
        return m_pParentNode;
    }

    void Node::SetParentNode(INode* pParentNode)
    {
        m_pParentNode = pParentNode;
    }

    void Node::CreateWnd(HWND hPWnd)
    {
        if (m_nHandle.IsZero())
        {
            CString strTagName = GetTagName();
            ::RefObject::IRefObject* pObj = g_pTangram->m_pObjectFactory->Create(strTagName, this);
            if (pObj != nullptr)
            {
                m_nHandle = pObj->GetHandle();
            }
        }
    }
}