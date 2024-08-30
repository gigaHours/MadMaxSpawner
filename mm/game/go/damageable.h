#pragma once

#include "physgo.h"
#include "mm/game/events.h"

class CDamageable : public CPhysicsGameObject, public NEvent::CEventHandler
{
public:
    void SetHealth(float fHealth);
    void SetInvulnerable(bool invulnerable) { m_Invulnerable = invulnerable; }

    bool m_Destroyed;
    bool m_Invulnerable;
    char unk234[214];
};