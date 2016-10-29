#ifndef GAMESKYRIMSE_H
#define GAMESKYRIMSE_H

#include "gamegamebryo.h"

#include <QObject>
#include <QtGlobal>

class GameSkyrimSE : public GameGamebryo
{
  Q_OBJECT
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
  Q_PLUGIN_METADATA(IID "org.tannin.GameSkyrimSE" FILE "gameskyrimSE.json")
#endif

public:

  GameSkyrimSE();

  virtual bool init(MOBase::IOrganizer *moInfo) override;

public: // IPluginGame interface

  virtual QString gameName() const override;
  virtual QList<MOBase::ExecutableInfo> executables() const override;
  virtual void initializeProfile(const QDir &path, ProfileSettings settings) const override;
  virtual QString savegameExtension() const override;
  virtual QString steamAPPId() const override;
  virtual QStringList primaryPlugins() const override;
  virtual QString binaryName() const override;
  virtual QString gameShortName() const override;
  virtual QStringList iniFiles() const override;
  virtual QStringList DLCPlugins() const override;
  virtual LoadOrderMechanism loadOrderMechanism() const override;
  virtual int nexusModOrganizerID() const override;
  virtual int nexusGameID() const override;

public: // IPlugin interface

  virtual QString name() const;
  virtual QString author() const;
  virtual QString description() const;
  virtual MOBase::VersionInfo version() const;
  virtual bool isActive() const;
  virtual QList<MOBase::PluginSetting> settings() const;
};

#endif // GAMESKYRIMSE_H
