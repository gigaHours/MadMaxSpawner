#include "avasingle.h"
#include "mm/std.h"
#include "mm/hookmgr.h"

#include "mm/core/graphics/graphicsengine.h"
#include "mm/core/input.h"

class CCharacterManager;

#define AVASINGLE(gog, steam, inst) inst*& CAvaSingle<inst>::Instance = *(inst**)ADDRESS(gog, steam);

AVASINGLE(0x1417116D0, 0x1417F4EC8, NGraphicsEngine::CGraphicsEngine);
AVASINGLE(0x141711708, 0x1417F4EF0, CDeviceManager);
AVASINGLE(0x141711B38, 0x1417F5338, CCharacterManager);