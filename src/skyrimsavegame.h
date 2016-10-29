#ifndef SKYRIMSESAVEGAME_H
#define SKYRIMSESAVEGAME_H

#include "gamebryosavegame.h"

namespace MOBase { class IPluginGame; }

class SkyrimSESaveGame : public GamebryoSaveGame
{
public:
  SkyrimSESaveGame(QString const &fileName, MOBase::IPluginGame const *game);
};

#endif // SKYRIMSESAVEGAME_H
