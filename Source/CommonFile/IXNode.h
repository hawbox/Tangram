#pragma once

class IXNode
{
public:
    IXNode() {};
    virtual ~IXNode() {};

    virtual ::RefObject::IRefObject* GetXObject() = 0;
};