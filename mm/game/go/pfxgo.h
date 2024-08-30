#pragma once

#include "mm/mm.h"
#include "go.h"

class IPfxInstance;
class IPfxGameObject
{
public:

    const struct __declspec(align(8)) SHitReactInfo
    {
        CVector3f m_Normal;
        CVector3f m_Position;
        float m_Impact;
        float m_IncomingImpact;
        IPfxGameObject* CollidableGameObjectA;
        IPfxGameObject* CollidableGameObjectB;
        const void* m_RigidBodyA;
        const void* m_RigidBodyB;
        CVector3f m_VelocityA;
        CVector3f m_VelocityB;
        bool m_RagdollImpact;
    };


    virtual ~IPfxGameObject() = 0;
    virtual IPfxInstance* GetPfxInstance() = 0;
    virtual void IPfxGameObject__Function02() = 0;
    virtual void IPfxGameObject__Function03() = 0;
    virtual void GetGameObjectId(SObjectID* result) = 0;
    virtual CRttiTypeId* GetTypeId() = 0;
    virtual bool IPfxGameObject__Function06() = 0;
    virtual bool IPfxGameObject__Function07() = 0;
    virtual void IPfxGameObject__Function08() = 0;
};