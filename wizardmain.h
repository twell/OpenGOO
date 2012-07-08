#ifndef WIZARDMAIN_H
#define WIZARDMAIN_H

#include <QWizard>
#include <QUuid>

#include "wizardgui_s0.h"
#include "wizardgui_s1.h"
#include "wizardgui_s2.h"
#include "wizardgui_s3.h"

#include "report.h"
#include "xmlmodule.h"

class WizardMain : public QWizard
{
    Q_OBJECT

private:
    void accept(); //Override.
    void init(QWidget *parent);

    Report *report;

    XmlModule *xml;

public:
    explicit WizardMain(QUuid uuid, QWidget *parent = 0);        //Launched by main.
    explicit WizardMain(Report *report, QWidget *parent = 0);    //Launched by ManagerGui.
    ~WizardMain();

    Report *getReport();

signals:
    void reportSended(Report*);

private slots:
    void wizardReportSended(Report*);

};

#endif // WIZARDMAIN_H
