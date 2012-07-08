#ifndef WIZARDGUI_S2_H
#define WIZARDGUI_S2_H

#include <QWizardPage>

#include "wizardmain.h"

namespace Ui {
    class WizardGui_s2;
}

class WizardGui_s2 : public QWizardPage
{
    Q_OBJECT

public:
    explicit WizardGui_s2(QWidget *parent = 0);
    ~WizardGui_s2();

private:
    Ui::WizardGui_s2 *ui;
    void showEvent(QShowEvent *); //Override.
};

#endif // WIZARDGUI_S2_H
