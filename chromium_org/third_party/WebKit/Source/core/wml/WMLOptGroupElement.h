/**
 * Copyright (C) 2009 Torch Mobile Inc. All rights reserved. (http://www.torchmobile.com/)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

#ifndef WMLOptGroupElement_h
#define WMLOptGroupElement_h

#if ENABLE(WML)
#include "WMLFormControlElement.h"
#include "core/wml/dummy/OptionGroupElement.h"

/// M: @{
#include "WMLNames.h"
/// @}

namespace WebCore {

class WMLOptGroupElement : public WMLFormControlElement, public OptionGroupElement {
public:
    static PassRefPtr<WMLOptGroupElement> create(const QualifiedName&, Document*);

    WMLOptGroupElement(const QualifiedName& tagName, Document*);
    virtual ~WMLOptGroupElement();

    virtual const AtomicString& formControlType() const;

    virtual bool rendererIsNeeded(RenderStyle*) { return false; }

    virtual void accessKeyAction(bool sendToAnyElement);
    virtual void childrenChanged(bool changedByParser = false, Node* beforeChange = 0, Node* afterChange = 0, int childCountDelta = 0);
    virtual void parseAttribute(const QualifiedName&, const AtomicString&) OVERRIDE;

    virtual void attach(const AttachContext& = AttachContext()) OVERRIDE;
    virtual void detach(const AttachContext& = AttachContext()) OVERRIDE;
    virtual void setRenderStyle(PassRefPtr<RenderStyle>);

    virtual String groupLabelText() const;

private:
    virtual RenderStyle* nonRendererRenderStyle() const;
    void recalcSelectOptions();

private:
    RefPtr<RenderStyle> m_style;
};

/// M: @{
inline bool isWMLOptGroupElement(const Node* node)
{
    return node->hasTagName(WMLNames::optgroupTag);
}

inline bool isWMLOptGroupElement(const Element* element)
{
    return element->hasTagName(WMLNames::optgroupTag);
}

inline WMLOptGroupElement* toWMLOptGroupElement(Node* node)
{
    ASSERT_WITH_SECURITY_IMPLICATION(!node || isWMLOptGroupElement(node));
    return static_cast<WMLOptGroupElement*>(node);
}
/// @}

}

#endif
#endif
