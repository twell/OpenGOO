#include "managergui.h"
#include "ui_managergui.h"

ManagerGui::ManagerGui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagerGui)
{
    ui->setupUi(this);

    //Tables init:

    //Those lines adapt the vertical headers within the content leaving users resize capabilities.
    ui->sendedTable->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    ui->unsendedTable->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);

    //Window init:

    this->centerWindow();
    setWindowTitle(tr("OpenGooDebugSenderTool Manager"));
    setWindowIcon(QIcon(":/res/images/res/icon.png"));

    startUp();

    //TODO: Check for new updates downloading the xml file with solved uuid.
}

void ManagerGui::centerWindow() {
    //Centers the window on the screen.

    // fixes the size on the window with widget hint.
    this->adjustSize();

    this->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            this->size(),
            qApp->desktop()->availableGeometry()
      ));
}

ManagerGui::~ManagerGui()
{
    delete ui;
}

void ManagerGui::sendReport() {
    //SLOT: gets the selected report from the unsended tableview and passes it to the wizard.

    QModelIndexList list = ui->unsendedTable->selectionModel()->selectedIndexes();
    QModelIndex index;

    if(!list.isEmpty())
        index = list.at(0);

    if(index.isValid()) {

        WizardMain *w = new WizardMain(model->getReport( unsendedProxy->mapToSource(index)));
        connect(w, SIGNAL(reportSended(Report*)),this, SLOT(reportSended(Report*)));

        w->show();

    } else {
        QMessageBox::information(this, tr("OpenGooDST"),
                                        tr("Select one report to be sent\n"
                                           "from the unsended ones."));
    }
}

void ManagerGui::sendTextualReport() {
    //Shows the textual report form.

    SendTextReportForm *sf = new SendTextReportForm(xml->getActualArch(), this);
    connect(sf, SIGNAL(reportSended(Report*)),this, SLOT(reportSended(Report*)));

    sf->show();
}

void ManagerGui::startUp() {
    //Starting function.

    xml = new XmlModule;                            //Interface to xml file.

    QList<Report*> *reports = xml->getReports();    //Retrieve a pointer list to the reports.
    model = new TablesModel(reports);               //Init table model.

    unsendedProxy = new CustomTableProxy(false);
    sendedProxy = new CustomTableProxy(true);

    unsendedProxy->setDynamicSortFilter(true);
    sendedProxy->setDynamicSortFilter(true);

    sendedProxy->setSourceModel(model);
    unsendedProxy->setSourceModel(model);

    ui->unsendedTable->setModel(unsendedProxy);
    ui->sendedTable->setModel(sendedProxy);
}

void ManagerGui::unsendedDoubleClicked ( const QModelIndex & index ) {
    //SLOT: Catches the double clicks from the unsended table.

    QModelIndex realIndex = unsendedProxy->mapToSource(index);
    Report *selectedReport = model->getReport(realIndex);

    ViewReport *viewReport = new ViewReport(selectedReport->getTextualDescription());
    viewReport->show();
}

void ManagerGui::sendedDoubleClicked ( const QModelIndex & index ) {
    //SLOT: Catches the double clicks from the sended table.

    QModelIndex realIndex = sendedProxy->mapToSource(index);
    Report *selectedReport = model->getReport(realIndex);

    ViewReport *viewReport = new ViewReport(selectedReport->getTextualDescription());
    viewReport->show();
}

TablesModel* ManagerGui::getDataModel() {
    return model;
}

void ManagerGui::reportSended(Report* sendedReport) {
    //SLOT: sets the "sended" flag of the just sended report and invalidates the proxy filter updating the tableviews.

    sendedReport->setSended(true);

    xml->save(); //The changes are saved on file.

    //Invalidation of proxies filter for tableview update.
    unsendedProxy->invalidate();
    sendedProxy->invalidate();
}




