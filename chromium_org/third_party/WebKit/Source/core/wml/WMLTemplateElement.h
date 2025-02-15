/*
 * Copyright (C) 2008, 2009 Torch Mobile Inc. All rights reserved. (http://www.torchmobile.com/)
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

#ifndef WMLTemplateElement_h
#define WMLTemplateElement_h

#if ENABLE(WML)
#include "WMLElement.h"
#include "WMLEventHandlingElement.h"

namespace WebCore {

class WMLTemplateElement : public WMLElement, public WMLEventHandlingElement {
public:
    static PassRefPtr<WMLTemplateElement> create(const QualifiedName&, Document*);

    WMLTemplateElement(const QualifiedName&, Document*);
    virtual ~WMLTemplateElement();

    virtual void parseAttribute(const QualifiedName&, const AtomicString&) OVERRIDE;

    static void registerTemplatesInDocument(Document*);
};

}

#endif
#endif
