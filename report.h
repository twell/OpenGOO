#ifndef REPORT_H
#define REPORT_H

#include <QString>
#include <QDateTime>
#include <QUuid>
#include <QVariant>

#include "architecture.h"

class Report
{
private:

    Architecture *arch;

    //Report data:
    QUuid uuid;
    QDateTime dateTime;
    QDateTime sendDate;
    QString debugText;
    QString userText;
    QString gameVerFix;

    bool sent;
    bool fixed;

public:
    Report(Architecture *arch, QUuid uuid, QDateTime dateTime, QString debugText, QString userText, bool sent, QDateTime sendDate, bool fixed, QString gameVerFix);

    //Setter functions:

    void setUserText(QString);
    void setFixed(bool);
    void setSent(bool);

    //Retrive data functions:

    Architecture* getArchP();

    QUuid getUuid();
    QString getgameVerFix() const;
    QString getGameVer() const;
    QDateTime getDateTime() const;
    QDateTime getSendDate() const;

    QString getDebugText() const;
    QString getUserText() const;

    bool getFixed() const;
    bool getSent() const;

    QString getTextualDescription();
};

#endif // REPORT_H
