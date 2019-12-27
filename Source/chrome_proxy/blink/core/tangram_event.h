// begin Add by TangramTeam
#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_EVENTS_TANGRAM_EVENT_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_EVENTS_TANGRAM_EVENT_H_

#include "third_party/blink/renderer/core/dom/events/Event.h"

namespace blink {

  class ScriptState;

  class CORE_EXPORT TangramEvent : public Event {
    DEFINE_WRAPPERTYPEINFO();

  public:
    static TangramEvent* Create() { return MakeGarbageCollected<TangramEvent>(); }

    static TangramEvent* Create(const AtomicString& event_type,
      const String& from,
      const String& to,
      const String& msgid,
      const String& payload,
      const String& extra);

    String from();
    void setFrom(const String&);
    String to();
    void setTo(const String&);
    String msgid();
    void setMsgid(const String&);
    String payload();
    void setPayload(const String&);
    String extra();
    void setExtra(const String&);

    ~TangramEvent() override;

    TangramEvent();

    TangramEvent(const AtomicString& event_type,
      const String& from,
      const String& to,
      const String& msgid,
      const String& payload,
      const String& extra);

  private:
    String from_;
    String to_;
    String msgid_;
    String payload_;
    String extra_;

  };

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_EVENTS_PROGRESS_EVENT_H_
// end Add by TangramTeam
