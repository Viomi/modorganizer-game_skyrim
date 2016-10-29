#ifndef SKYRIMSESCRIPTEXTENDER_H
#define SKYRIMSESCRIPTEXTENDER_H

#include "gamebryoscriptextender.h"

class GameGamebryo;

class SkyrimSEScriptExtender : public GamebryoScriptExtender
{
public:
  SkyrimSEScriptExtender(const GameGamebryo *game);

  virtual QString name() const override;

  virtual QStringList saveGameAttachmentExtensions() const override;

};

#endif // SKYRIMSESCRIPTEXTENDER_H
