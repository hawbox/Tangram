#pragma once

#include "../CommonFile/IGui.h"

class IXmlReader;

namespace Gui
{
    // As an XCML fragment.
    class Document : public IDocument
    {
    public:
        Document();
        virtual ~Document() {};

        void Load(PCWSTR pszXcml) override;
        INode* GetRoot() override;
        void CreateWnd(HWND hPWnd) override;
    private:
        HWND m_hInvisibleHWnd;
        INode* m_pRootNode;

        IStream* LoadXcmlAsStream(PCWSTR lpXcml);
        INode* CreateNodeTreeFromXcml(IStream* pXcmlStream);
        void ReadAttributes(IXmlReader* pReader, INode* pNode);
        void RemoveChildWindows(HWND hPWnd);
    };
}