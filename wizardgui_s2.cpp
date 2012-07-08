#include "wizardgui_s2.h"
#include "ui_wizardgui_s2.h"

#include <QDebug>

WizardGui_s2::WizardGui_s2(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::WizardGui_s2)
{
    ui->setupUi(this);
}

WizardGui_s2::~WizardGui_s2()
{
    delete ui;
}

void WizardGui_s2::showEvent(QShowEvent *) {

    wizard()->setButtonText(QWizard::NextButton, tr("&Invia!"));
    wizard()->setButtonText(QWizard::BackButton, tr("&Indietro"));

    //Generating the textual report::

    QString userText = wizard()->field("UserDescription").toString(); //User description inserted previously.

    WizardMain* wizardPointer= dynamic_cast<WizardMain*>(wizard());
    Report *reportPointer = wizardPointer->getReport();
    reportPointer->setUserText(userText);

    ui->bugReport->setText(reportPointer->getTextualDescription());
}
