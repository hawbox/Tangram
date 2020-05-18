#include "../stdafx.h"
#include "Document.h"
#include "Node.h"
#include <xmllite.h>
#include "../TangramCore.h"

extern CTangram* g_pTangram;

namespace Gui
{
    Document::Document()
    {
        m_hInvisibleHWnd = 0;
        m_pRootNode = nullptr;
    }

    void Document::Load(PCWSTR pszXcml)
    {
        IStream* pXcmlSteam = LoadXcmlAsStream(pszXcml);
        m_pRootNode = CreateNodeTreeFromXcml(pXcmlSteam);
        pXcmlSteam->Release();
    }

    INode* Document::GetRoot()
    {
        return m_pRootNode;
    }

    void Document::CreateWnd(HWND hPWnd)
    {
        if (m_pRootNode != nullptr)
        {
            if (::IsWindow(hPWnd))
            {
                RemoveChildWindows(hPWnd);
            }
            m_pRootNode->CreateWnd(hPWnd);
        }
    }

    IStream* Document::LoadXcmlAsStream(PCWSTR pswzXcml)
    {
        USES_CONVERSION;
        // Tips: IXmlReader cannot parse wide byte strings.
        const PCSTR pszXcml = W2A(pswzXcml);
        IStream* iStream = ::SHCreateMemStream((const BYTE*)pszXcml, strlen(pszXcml));
        return iStream;
    }

    INode* Document::CreateNodeTreeFromXcml(IStream* pXcmlStream)
    {
        HRESULT hr;
        IXmlReader* pXmlReader;
        XmlNodeType nodeType;

        hr = ::CreateXmlReader(IID_PPV_ARGS(&pXmlReader), nullptr);
        hr = pXmlReader->SetProperty(XmlReaderProperty_DtdProcessing, DtdProcessing_Prohibit);
        hr = pXmlReader->SetInput(pXcmlStream);

        // Node information
        INode* pRootNode = nullptr;
        INode* pParentNode = nullptr;
        INode* pCurNode = nullptr;

        PCWSTR pswzPrefix = nullptr;
        PCWSTR pswzLocalName = nullptr;
        PCWSTR pswzValue = nullptr;

        UINT nPrefixSize = 0;
        UINT nLocalNameSize = 0;
        UINT nValueSize = 0;

        // Reads all nodes
        while (S_OK == (hr = pXmlReader->Read(&nodeType)))
        {
            switch (nodeType)
            {
            case XmlNodeType_Element:
                pCurNode = new Node();
                hr = pXmlReader->GetPrefix(&pswzPrefix, &nPrefixSize);
                hr = pXmlReader->GetLocalName(&pswzLocalName, &nLocalNameSize);
                if (FAILED(hr))
                {
                    continue;
                }
                pCurNode->SetTagName(nPrefixSize > 0 ? CString(pswzPrefix) +
                    _T(":") + CString(pswzLocalName) : CString(pswzLocalName));
                ReadAttributes(pXmlReader, pCurNode);
                // First element as root node
                if (pRootNode == nullptr)
                {
                    pRootNode = pCurNode;
                }
                if (pParentNode != nullptr)
                {
                    pParentNode->AddChildNode(pCurNode);
                    pCurNode->SetParentNode(pParentNode);
                }
                // Go inside this node.
                pParentNode = pCurNode;
                pCurNode = nullptr;
                break;
            case XmlNodeType_EndElement:
                // Exit this node.
                if (pParentNode != nullptr)
                {
                    pParentNode = pParentNode->GetParentNode();
                }
                break;
            case XmlNodeType_Text:
                if (pParentNode != nullptr)
                {
                    hr = pXmlReader->GetValue(&pswzValue, &nValueSize);
                    if (FAILED(hr))
                    {
                        continue;
                    }
                    pParentNode->SetText(CString(pswzValue));
                }
                break;
            default:
                break;
            }
        }

        return pRootNode;
    }

    void Document::ReadAttributes(IXmlReader* pReader, INode* pNode)
    {
        HRESULT hr;
        if (S_OK != (hr = pReader->MoveToFirstAttribute()))
        {
            return;
        }
        for (;;)
        {
            if (!pReader->IsDefault())
            {
                PCWSTR pswzPrefix = nullptr;
                PCWSTR pswzLocalName = nullptr;
                PCWSTR pswzValue = nullptr;

                UINT nPrefixSize = 0;
                UINT nLocalNameSize = 0;
                UINT nValueSize = 0;

                hr = pReader->GetPrefix(&pswzPrefix, &nPrefixSize);
                hr = pReader->GetLocalName(&pswzLocalName, &nLocalNameSize);
                hr = pReader->GetValue(&pswzValue, &nValueSize);
                if (FAILED(hr))
                {
                    continue;
                }
                pNode->SetAttribute(nPrefixSize > 0 ? CString(pswzPrefix) + 
                    _T(":") + CString(pswzLocalName) : CString(pswzLocalName), pswzValue);
            }
            if (S_OK != (hr = pReader->MoveToNextAttribute()))
            {
                break;
            }
        }
    }

    BOOL CALLBACK RemoveChildWindowProc(_In_ HWND hwnd, _In_ LPARAM lParam)
    {
        HWND hInvisibleHWnd = (HWND)lParam;
        ::SetParent(hwnd, hInvisibleHWnd);
        return TRUE;
    }

    void Document::RemoveChildWindows(HWND hPWnd)
    {
        if (::IsWindow(hPWnd))
        {
            if (!::IsWindow(m_hInvisibleHWnd))
            {
                m_hInvisibleHWnd = g_pTangram->m_pXWindows->CreateInvisibleWnd(hPWnd);
            }
            ::EnumChildWindows(hPWnd, RemoveChildWindowProc, (LPARAM)m_hInvisibleHWnd);
        }
    }
}