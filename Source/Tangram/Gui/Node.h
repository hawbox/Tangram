#pragma once

#include <vector>
#include <map>
#include "../CommonFile/IGui.h"
#include "../CommonFile/IRefObject.h"

namespace Gui
{
    class Node : public INode
    {
    public:
        Node();
        virtual ~Node() {};

        CString GetTagName() override;
        void SetTagName(CString strTagName) override;
        CString GetText() override;
        void SetText(CString strText) override;
        CString GetAttribute(CString strName) override;
        void SetAttribute(CString strName, CString strValue) override;
        int64_t GetAttributeAsNumber(CString strName) override;
        void SetAttribute(CString strName, int64_t nValue) override;
        std::vector<INode*> GetChildNodes() override;
        void AddChildNode(INode* pNode) override;
        INode* GetParentNode() override;
        void SetParentNode(INode* pParentNode) override;
        HWND GetParentHWND() override;
        void CreateWnd(HWND hPWnd) override;

    private:
        HWND m_hPWnd;
        ::RefObject::Handle m_nHandle;

        CString m_strTagName;
        CString m_strInnerText;
        std::map<CString, CString> m_mapAttributes;

        INode* m_pParentNode;
        std::vector<INode*> m_vecChildNodes;
    };
}