/**
 * Copyright (C) 2008 Torch Mobile Inc. All rights reserved. (http://www.torchmobile.com/)
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

#ifndef WMLDoElement_h
#define WMLDoElement_h

#if ENABLE(WML)
#include "WMLElement.h"

namespace WebCore {

class WMLTaskElement;

class WMLDoElement : public WMLElement {
public:
    static PassRefPtr<WMLDoElement> create(const QualifiedName& tagName, Document*);

    WMLDoElement(const QualifiedName& tagName, Document*);

    virtual void defaultEventHandler(Event*);
    virtual void parseAttribute(const QualifiedName&, const AtomicString&) OVERRIDE;
    virtual InsertionNotificationRequest insertedInto(ContainerNode*) OVERRIDE;
    virtual void removedFrom(ContainerNode*) OVERRIDE;

    virtual bool canContainRangeEndPoint() const { return false; }

    virtual void attach(const AttachContext& = AttachContext()) OVERRIDE;

    virtual RenderObject* createRenderer(RenderStyle*);
    virtual void recalcStyle(StyleChange);

    void registerTask(WMLTaskElement*);
    void deregisterTask(WMLTaskElement*);

    bool isActive() const { return m_isActive; }
    String label() const;
    String name() const { return m_name; }

    void setActive(bool active) { m_isActive = active; }
    void setNoop(bool noop) { m_isNoop = noop;}

private:
    WMLTaskElement* m_task;
    bool m_isActive;
    bool m_isNoop;
    bool m_isOptional;
    String m_name;
    String m_type;
};

}

#endif
#endif
