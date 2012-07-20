#include <QDebug>

#include "wizardmain.h"

WizardMain::WizardMain(QUuid uuid, QWidget *parent) : //Launched by main.
    QWizard(parent)
{
    init(parent);

    connect(this, SIGNAL(reportSent(Report*)),this, SLOT(wizardReportSent(Report*)));

    //Opens the xml file calling the XmlModule and loads the report with same uuid.

    xml = new XmlModule;

    Report* rep = xml->getByUuid(uuid);

    if(rep != NULL) {

        this->report = rep;

    } else return;
}

WizardMain::~WizardMain() {
    delete xml;
}

WizardMain::WizardMain(Report *report, QWidget *parent) : //Launched by ManagerGui.
    QWizard(parent)
{
    init(parent);
    this->report = report;
}

void WizardMain::init(QWidget *parent) {

    addPage(new WizardGui_s0);
    addPage(new WizardGui_s1);
    addPage(new WizardGui_s2);
    addPage(new WizardGui_s3);

    QList<QWizard::WizardButton> layout;
    layout << QWizard::Stretch << QWizard::Stretch << QWizard::Stretch << QWizard::Stretch << QWizard::CancelButton << QWizard::BackButton << QWizard::Stretch << QWizard::NextButton << QWizard::FinishButton;
    setOption(QWizard::NoBackButtonOnStartPage, true);
    setOption(QWizard::NoBackButtonOnLastPage, true);
    setOption(QWizard::NoCancelButton);
    setButtonLayout(layout);

    setWindowTitle(tr("OpenGooDebugToolSender"));
    setWindowIcon(QIcon(":/res/images/res/icon.png"));
}

void WizardMain::accept() {
    //The wizard is accepted when the user clicks on finished.

    emit reportSent(report);  //TODO: Move the emit line where the report is correctly sent!
    QWizard::accept();
}

Report* WizardMain::getReport() {
    return report;
}

void WizardMain::wizardReportSent(Report* wizardSentReport) {
    //SLOT: sets the "sent" flag of the just sent report.

    wizardSentReport->setSent(true);
    xml->save(); //The changes are saved on file.
}
