#include "sendtextreportform.h"
#include "ui_sendtextreportform.h"

SendTextReportForm::SendTextReportForm(Architecture* arch, ManagerGui *guiPointer) :
    QWidget(),
    ui(new Ui::SendTextReportForm)
{
    ui->setupUi(this);
    this->centerWindow();

    this->guiPointer = guiPointer;

    setWindowTitle(tr("OpenGooDebugSenderTool - send notification"));
    setWindowIcon(QIcon(":/res/images/res/icon.png"));

    archInUse = arch;
}

SendTextReportForm::~SendTextReportForm()
{
    delete ui;
}

void SendTextReportForm::centerWindow() {
    //Centers the window on the screen.

    //Fixes the size on the window with widget hint.
    this->adjustSize();

    this->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            this->size(),
            qApp->desktop()->availableGeometry()
      ));
}

void SendTextReportForm::sendTextualReport() {

    int ret = QMessageBox::question(this, tr("My OpenGooDST"),
                                    tr("Send the report.\n"
                                       "Are you sure you want to send the report?"),
                                    QMessageBox::Yes | QMessageBox::Cancel );
    switch(ret) {

        case QMessageBox::Yes:
            qWarning() << "Yes!";

            //Generate the report!

            report = new Report(archInUse, QUuid::createUuid(), QDateTime().currentDateTimeUtc(), QString(), ui->userText->toPlainText(), false, QDateTime(), false, QString());

            guiPointer->getDataModel()->insertRows(report, 0, 1, QModelIndex());

            emit reportSended(report);

            emit close();

            break;

        case QMessageBox::Cancel:
            qWarning() << "Cancel!";
            break;

    }

}
