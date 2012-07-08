#ifndef ARCHITECTURE_H
#define ARCHITECTURE_H

#include <QString>
#include <QObject>

class Architecture {

public:
    Architecture(QString os, QString build, QString gameVer, QString arch, QString driverVer, QString vga, bool inUse);

    //Retrive data functions;
    QString getOs() const;
    QString getGameVer() const;
    QString getBuild() const;
    QString getArch() const;
    QString getVga() const;
    QString getDriverVer() const;
    bool getInUse() const;

private:
    QString os;
    QString build;
    QString gameVer;
    QString arch;
    QString driverVer;
    QString vga;
    bool inUse;
};

#endif // ARCHITECTURE_H
