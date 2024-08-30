#pragma once

#include "damageable.h"

// temp
class IPfxCharacter
{
public:
	virtual ~IPfxCharacter() = 0;
	virtual class CCharacter* GetPfxGameObject() = 0;
};

namespace NCharacterSystem
{
	class CCharacterBase : public IPfxCharacter, public CRtti
	{
	public:
	};
}

class CCharacter : public CDamageable, public NCharacterSystem::CCharacterBase, public IPhysicsGameObjectListenable
{
public:
	// SUS
};