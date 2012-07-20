#ifndef MANAGERGUI_H
#define MANAGERGUI_H

#include <QWidget>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QTableWidgetItem>
#include <QSortFilterProxyModel>
#include <QFile>
#include <QDebug>

#include "sendtextreportform.h"
#include "customtableproxy.h"
#include "wizardmain.h"
#include "viewreport.h"
#include "xmlmodule.h"
#include "tablesmodel.h"

namespace Ui {
    class ManagerGui;
}

class ManagerGui : public QWidget
{
    Q_OBJECT

public:
    explicit ManagerGui(QWidget *parent = 0);
    ~ManagerGui();

    TablesModel* getDataModel();

private:
    Ui::ManagerGui *ui;
    void centerWindow();    //Center the window on the screen.
    void startUp();         //Starting function.

    //Table functions and data:

    XmlModule *xml;

    TablesModel *model;
    CustomTableProxy *notSentProxy;
    CustomTableProxy *sentProxy;

private slots:
    void sendReport();
    void sendTextualReport();

    void notSentDoubleClicked ( const QModelIndex & index );
    void sentDoubleClicked ( const QModelIndex & index );

    void reportSent(Report*);
};

#endif // MANAGERGUI_H
