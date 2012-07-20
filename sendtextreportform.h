#ifndef SENDTEXTREPORTFORM_H
#define SENDTEXTREPORTFORM_H

#include <QWidget>
#include <QDesktopWidget>
#include <QMessageBox>

#include <QDebug>

#include "report.h"
#include "architecture.h"
#include "managergui.h"

namespace Ui {
    class SendTextReportForm;
}

class ManagerGui;

class SendTextReportForm : public QWidget
{
    Q_OBJECT

public:
    explicit SendTextReportForm(Architecture*, ManagerGui *parent = 0);
    ~SendTextReportForm();

private:
    Ui::SendTextReportForm *ui;

    void centerWindow();     //Center the window on the screen.

    Report *report;          //The generated report.
    Architecture *archInUse; //The arch actually in use by the game.

    ManagerGui *guiPointer;

signals:
    void reportSent(Report*);

private slots:
    void sendTextualReport();
};

#endif // SENDTEXTREPORTFORM_H
