#include "skyrimSEbsainvalidation.h"

SkyrimSEBSAInvalidation::SkyrimSEBSAInvalidation(DataArchives *dataArchives, MOBase::IPluginGame const *game)
  : GamebryoBSAInvalidation(dataArchives, "skyrim.ini", game)
{
}

QString SkyrimSEBSAInvalidation::invalidationBSAName() const
{
  return "SkyrimSE - Invalidation.bsa";
}

unsigned long SkyrimSEBSAInvalidation::bsaVersion() const
{
  return 0x68;
}
