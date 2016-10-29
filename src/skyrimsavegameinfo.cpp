#include "skyrimSEsavegameinfo.h"

#include "skyrimSEsavegame.h"
#include "gamegamebryo.h"

SkyrimSESaveGameInfo::SkyrimSESaveGameInfo(GameGamebryo const *game) :
  GamebryoSaveGameInfo(game)
{
}

SkyrimSESaveGameInfo::~SkyrimSESaveGameInfo()
{
}


MOBase::ISaveGame const *SkyrimSESaveGameInfo::getSaveGameInfo(QString const &file) const
{
  return new SkyrimSESaveGame(file, m_Game);
}
