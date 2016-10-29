#include "gameskyrimSE.h"

#include "skyrimSEbsainvalidation.h"
#include "skyrimSEscriptextender.h"
#include "skyrimSEdataarchives.h"
#include "skyrimSEsavegameinfo.h"

#include "executableinfo.h"
#include "pluginsetting.h"

#include <gamebryolocalsavegames.h>
#include <gamebryogameplugins.h>
#include <gamebryounmanagedmods.h>

#include <QCoreApplication>
#include <QDebug>
#include <QFileInfo>

#include <QtDebug>

#include <Windows.h>
#include <winver.h>

#include <exception>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

using namespace MOBase;

GameSkyrimSE::GameSkyrimSE()
{
}

bool GameSkyrimSE::init(IOrganizer *moInfo)
{
  if (!GameGamebryo::init(moInfo)) {
    return false;
  }
  registerFeature<ScriptExtender>(new SkyrimSEScriptExtender(this));
  registerFeature<DataArchives>(new SkyrimSEDataArchives());
  registerFeature<BSAInvalidation>(new SkyrimSEBSAInvalidation(feature<DataArchives>(), this));
  registerFeature<SaveGameInfo>(new SkyrimSESaveGameInfo(this));
  registerFeature<LocalSavegames>(new GamebryoLocalSavegames(myGamesPath(), "skyrim.ini"));
  registerFeature<GamePlugins>(new GamebryoGamePlugins(moInfo));
  registerFeature<UnmanagedMods>(new GamebryoUnmangedMods(this));
  return true;
}

QString GameSkyrimSE::gameName() const
{
  return "Skyrim Special Edition";
}

QList<ExecutableInfo> GameSkyrimSE::executables() const
{
  return QList<ExecutableInfo>()
      << ExecutableInfo("SKSE", findInGameFolder(feature<ScriptExtender>()->loaderName()))
      << ExecutableInfo("SBW", findInGameFolder("SBW.exe"))
      << ExecutableInfo("SkyrimSE", findInGameFolder(binaryName()))
      << ExecutableInfo("SkyrimSE Launcher", findInGameFolder(getLauncherName()))
      << ExecutableInfo("BOSS", findInGameFolder("BOSS/BOSS.exe"))
      << ExecutableInfo("LOOT", getLootPath())
      << ExecutableInfo("Creation Kit", findInGameFolder("CreationKit.exe")).withSteamAppId("202480")
  ;
}

QString GameSkyrimSE::name() const
{
  return "Skyrim SE Support Plugin";
}

QString GameSkyrimSE::author() const
{
  return "Tannin, Viomi, MinSin";
}

QString GameSkyrimSE::description() const
{
  return tr("Adds support for the game Skyrim SE");
}

MOBase::VersionInfo GameSkyrimSE::version() const
{
  return VersionInfo(1, 0, 0, VersionInfo::RELEASE_FINAL);
}

bool GameSkyrimSE::isActive() const
{
  return qApp->property("managed_game").value<IPluginGame*>() == this;
}

QList<PluginSetting> GameSkyrimSE::settings() const
{
  return QList<PluginSetting>();
}

void GameSkyrimSE::initializeProfile(const QDir &path, ProfileSettings settings) const
{
  if (settings.testFlag(IPluginGame::MODS)) {
    copyToProfile(localAppFolder() + "/Skyrim Special Edition", path, "plugins.txt");
    copyToProfile(localAppFolder() + "/Skyrim Special Edition", path, "loadorder.txt");
  }

  if (settings.testFlag(IPluginGame::CONFIGURATION)) {
    if (settings.testFlag(IPluginGame::PREFER_DEFAULTS)
        || !QFileInfo(myGamesPath() + "/skyrim.ini").exists()) {
      copyToProfile(gameDirectory().absolutePath(), path, "skyrim_default.ini", "skyrim.ini");
    } else {
      copyToProfile(myGamesPath(), path, "skyrim.ini");
    }

    copyToProfile(myGamesPath(), path, "skyrimprefs.ini");
  }
}

QString GameSkyrimSE::savegameExtension() const
{
  return "ess";
}

QString GameSkyrimSE::steamAPPId() const
{
  return "489830";
}

QStringList GameSkyrimSE::primaryPlugins() const
{
  return { "skyrim.esm", "update.esm" };
}

QString GameSkyrimSE::binaryName() const
{
  return "SkyrimSE.exe";
}

QString GameSkyrimSE::gameShortName() const
{
  return "SkyrimSE";
}

QStringList GameSkyrimSE::iniFiles() const
{
  return { "skyrim.ini", "skyrimprefs.ini" };
}

QStringList GameSkyrimSE::DLCPlugins() const
{
  return { "Dawnguard.esm", "Dragonborn.esm", "HearthFires.esm" };
}

namespace {
//Note: This is ripped off from shared/util. And in an upcoming move, the fomod
//installer requires something similar. I suspect I should abstract this out
//into gamebryo (or lower level)

VS_FIXEDFILEINFO GetFileVersion(const std::wstring &fileName)
{
  DWORD handle = 0UL;
  DWORD size = ::GetFileVersionInfoSizeW(fileName.c_str(), &handle);
  if (size == 0) {
    throw std::runtime_error("failed to determine file version info size");
  }

  std::vector<char> buffer(size);
  handle = 0UL;
  if (!::GetFileVersionInfoW(fileName.c_str(), handle, size, buffer.data())) {
    throw std::runtime_error("failed to determine file version info");
  }

  void *versionInfoPtr = nullptr;
  UINT versionInfoLength = 0;
  if (!::VerQueryValue(buffer.data(), L"\\", &versionInfoPtr, &versionInfoLength)) {
    throw std::runtime_error("failed to determine file version");
  }

  return *static_cast<VS_FIXEDFILEINFO*>(versionInfoPtr);
}

}

IPluginGame::LoadOrderMechanism GameSkyrimSE::loadOrderMechanism() const
{
  try {
    std::wstring fileName = gameDirectory().absoluteFilePath(binaryName()).toStdWString().c_str();
    VS_FIXEDFILEINFO versionInfo = ::GetFileVersion(fileName);
    if ((versionInfo.dwFileVersionMS > 0x10004) || // version >= 1.0.x?
        ((versionInfo.dwFileVersionMS == 0x10004) && (versionInfo.dwFileVersionLS >= 0x1A0000))) { // version >= ?.4.26
      return LoadOrderMechanism::PluginsTxt;
    }
  } catch (const std::exception &e) {
    qCritical() << "SkyrimSE.exe is invalid: " << e.what();
  }
  return LoadOrderMechanism::FileTime;
}


int GameSkyrimSE::nexusModOrganizerID() const
{
  return 1335;
}

int GameSkyrimSE::nexusGameID() const
{
  return 1704;
}
