#pragma once

#include <QString>

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

class DesktopEntryWriter {
public:
    static DesktopAppResult write(const DesktopAppConfig &config);
    static QString validate(const DesktopAppConfig &config);

private:
    static QString appIdFromName(const QString &name);
    static QString desktopEntryText(const DesktopAppConfig &config, const QString &iconPath);
    static QString desktopArgumentQuote(const QString &value);
    static void ensureDirectory(const QString &path);
    static QString installIcon(const QString &appId, const QString &sourcePath);
};
