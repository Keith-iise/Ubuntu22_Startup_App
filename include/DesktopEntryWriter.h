#pragma once

#include <QString>
#include <QVector>

struct DesktopAppConfig {
    QString appName;
    QString command;
    QString iconPath;
    bool autostart = false;
};

struct DesktopAppResult {
    QString appId;
    QString desktopFilePath;
    QString autostartFilePath;
    QString installedIconPath;
};

struct DesktopAppInfo {
    QString appId;
    QString appName;
    QString desktopFilePath;
    QString autostartFilePath;
    QString installedIconPath;
};

class DesktopEntryWriter {
public:
    static DesktopAppResult write(const DesktopAppConfig &config);
    static QString validate(const DesktopAppConfig &config);
    static QVector<DesktopAppInfo> generatedApplications();
    static DesktopAppInfo findGeneratedApplication(const QString &appId);
    static void removeGeneratedApplication(const QString &appId);

private:
    static QString appIdFromName(const QString &name);
    static QString desktopEntryText(const DesktopAppConfig &config, const QString &iconPath);
    static QString desktopArgumentQuote(const QString &value);
    static void ensureDirectory(const QString &path);
    static QString installIcon(const QString &appId, const QString &sourcePath);
};
