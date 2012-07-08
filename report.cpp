#include "report.h"

Report::Report(Architecture *arch, QUuid uuid, QDateTime dateTime, QString debugText, QString userText, bool sended, QDateTime sendDate, bool fixed, QString gameVerFix)
{
    this->arch = arch;
    this->uuid = uuid;
    this->dateTime = dateTime;
    this->debugText = debugText;
    this->userText = userText;
    this->sended = sended;
    this->sendDate = sendDate;
    this->fixed = fixed;
    this->gameVerFix = gameVerFix;
}

      //-------------------------//
     // -   Setter functions  - //
    //-------------------------//

void Report::setUserText(QString userText) {
    this->userText = userText;
}

void Report::setFixed(bool fixed) {
    this->fixed = fixed;
}

void Report::setSended(bool sended) {
    this->sended = sended;
}

      //------------------------------//
     // -  Retrive data functions  - //
    //------------------------------//

QString Report::getGameVer() const {
    return arch->getGameVer();
}

QDateTime Report::getDateTime() const {
    return dateTime;
}

QDateTime Report::getSendDate() const {
    return sendDate;
}

bool Report::getFixed() const {
    return fixed;
}

QString Report::getgameVerFix() const {
    return gameVerFix;
}

bool Report::getSended() const {
    return sended;
}

QString Report::getDebugText() const {
    return debugText;
}

QString Report::getUserText() const {
    return userText;
}

QString Report::getTextualDescription() {
    //Generates the textual description that will be sended.

    QString textualReport;

    textualReport.append( "OpenGooDTS Report " + uuid.toString() + " generated on " + dateTime.toString() +"\n"
                          + "-----------------------------------------------------\n"
                          + "-                      Architecture                      -\n"
                          + "-----------------------------------------------------\n"
                          + "- " + arch->getGameVer() + " in " + arch->getBuild() + "\n"
                          + "- " + arch->getOs() + "  on " + arch->getArch() + " with " + arch->getVga() + ", " + arch->getDriverVer() + "\n"
                          + "-----------------------------------------------------\n"
                          + "-                         Report                            -\n"
                          + "-----------------------------------------------------\n"
                          + "-Tracer=\n"
                          + getDebugText()+"\n"
                          + "-UserDescription=\n"
                          + getUserText()+"\n"
                          + "-----------------------------------------------------\n"
                          + "Sended on " + sendDate.toString() + "\n");

    return textualReport;
}

QUuid Report::getUuid() {
    return uuid;
}

Architecture* Report::getArchP() {
    return arch;
}


