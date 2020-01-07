#pragma once

#include "IRefObject.h"

namespace Gui
{
    class IXWindows;
    class IDocument;
    class INode;

    //class IGuiFactoryDelegate : public ::RefObject::IFactoryDelegate
    //{
    //public:
    //    IGuidFactoryDelegate() 
    //    {
    //        m_nId = 0;
    //    };
    //    virtual ~IGuidFactoryDelegate() {};

    //    uint8_t GetHeaderOfHandle()
    //    {
    //        if (m_nId == 0)
    //        {
    //            m_nId = m_pObjectFactory->GenerateNewFactoryId();
    //        }
    //        return m_nId;
    //    } override;

    //protected:
    //    uint8_t m_nId;
    //};

    class IXWindows
    {
    public:
        IXWindows() {};
        virtual ~IXWindows() {};

        virtual HWND CreateInvisibleWnd(HWND hPWnd) = 0;
    };

    class IDocument
    {
    public:
        IDocument() {};
        virtual ~IDocument() {};

        virtual void Load(PCWSTR pszXcml) = 0;
        virtual void CreateWnd(HWND hPWnd) = 0;
    };

    class INode
    {
    public:
        INode() {};
        virtual ~INode() {};

        virtual CString GetTagName() = 0;
        virtual void SetTagName(CString strTagName) = 0;
        virtual CString GetText() = 0;
        virtual void SetText(CString strText) = 0;
        virtual CString GetAttribute(CString strName) = 0;
        virtual void SetAttribute(CString strName, CString strValue) = 0;
        virtual int64_t GetAttributeAsNumber(CString strName) = 0;
        virtual void SetAttribute(CString strName, int64_t nValue) = 0;
        virtual std::vector<INode*> GetChildNodes() = 0;
        virtual void AddChildNode(INode* pNode) = 0;
        virtual INode* GetParentNode() = 0;
        virtual void SetParentNode(INode* pParentNode) = 0;
        virtual HWND GetParentHWND() = 0;
        virtual void CreateWnd(HWND hPWnd) = 0;
    };
}