// Copyright 2020 The Tangram Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/core/html/html_new_element.h"
#include "base/json/json_reader.h"
#include "base/json/json_writer.h"
#include "base/values.h"
#include "base/guid.h"

using namespace base;

namespace blink {

HTMLNewElement::HTMLNewElement(const QualifiedName& tag_name,
                                       Document& document)
    : HTMLElement(tag_name, document) {
  reference_id_ = GenerateGUID();
}

void HTMLNewElement::OnFinishParsingChildren() const {
  DictionaryValue dict;
  dict.SetStringKey("referenceId", reference_id_);
  dict.SetStringKey("action", "finish_parsing_children");
  dict.SetStringKey("localName", localName().Utf8());
  dict.SetStringKey("outerHTML", OuterHTMLAsString().Utf8());
  std::string json;
  JSONWriter::Write(dict, &json);
  GetDocument().SendCustomMessage(json);
}

void HTMLNewElement::OnAttributeChanged(const std::string name,
    const std::string old_value,
    const std::string new_value) const {
  DictionaryValue dict;
  dict.SetStringKey("referenceId", reference_id_);
  dict.SetStringKey("action", "attribute_changed");
  dict.SetStringKey("localName", localName().Utf8());
  dict.SetStringKey("attrName", name);
  dict.SetStringKey("oldValue", old_value);
  dict.SetStringKey("newValue", new_value);
  dict.SetStringKey("outerHTML", OuterHTMLAsString().Utf8());
  std::string json;
  JSONWriter::Write(dict, &json);
  GetDocument().SendCustomMessage(json);
}

}  // namespace blink
