#pragma once
#include "ai/Monsters/state.h"

template <typename _Object>
class CStateBloodsuckerVampireApproach : public CState<_Object>
{
    typedef CState<_Object> inherited;

public:
    CStateBloodsuckerVampireApproach(_Object* obj);
    virtual ~CStateBloodsuckerVampireApproach();

    virtual void initialize();
    virtual void execute();
    virtual void remove_links(IGameObject* object) { inherited::remove_links(object); }
};

#include "bloodsucker_vampire_approach_inline.h"
