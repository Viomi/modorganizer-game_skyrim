#ifndef SKYRIMSEBSAINVALIDATION_H
#define SKYRIMSEBSAINVALIDATION_H


#include "gamebryobsainvalidation.h"
#include "skyrimSEdataarchives.h"

#include <memory>

class SkyrimSEBSAInvalidation : public GamebryoBSAInvalidation
{
public:

  SkyrimSEBSAInvalidation(DataArchives *dataArchives, MOBase::IPluginGame const *game);

private:

  virtual QString invalidationBSAName() const override;
  virtual unsigned long bsaVersion() const override;

};

#endif // SKYRIMSEBSAINVALIDATION_H
