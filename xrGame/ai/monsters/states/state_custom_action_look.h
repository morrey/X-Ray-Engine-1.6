#pragma once
#include "ai/Monsters/state.h"
#include "state_data.h"

template <typename _Object>
class CStateMonsterCustomActionLook : public CState<_Object>
{
    typedef CState<_Object> inherited;

    SStateDataActionLook data;

public:
    CStateMonsterCustomActionLook(_Object* obj);
    virtual ~CStateMonsterCustomActionLook();

    virtual void execute();
    virtual bool check_completion();
    virtual void remove_links(IGameObject* object) { inherited::remove_links(object); }
};

#include "state_custom_action_look_inline.h"
