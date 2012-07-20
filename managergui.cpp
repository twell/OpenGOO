#include "managergui.h"
#include "ui_managergui.h"

ManagerGui::ManagerGui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagerGui)
{
    ui->setupUi(this);

    //Tables init:

    //Those lines adapt the vertical headers within the content leaving users resize capabilities.
    ui->sentTable->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    ui->notSentTable->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);

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
    //SLOT: gets the selected report from the not sent tableview and passes it to the wizard.

    QModelIndexList list = ui->notSentTable->selectionModel()->selectedIndexes();
    QModelIndex index;

    if(!list.isEmpty())
        index = list.at(0);

    if(index.isValid()) {

        WizardMain *w = new WizardMain(model->getReport( notSentProxy->mapToSource(index)));
        connect(w, SIGNAL(reportSent(Report*)),this, SLOT(reportSent(Report*)));

        w->show();

    } else {
        QMessageBox::information(this, tr("OpenGooDST"),
                                        tr("Select one report to be sent\n"
                                           "from the not sent ones."));
    }
}

void ManagerGui::sendTextualReport() {
    //Shows the textual report form.

    SendTextReportForm *sf = new SendTextReportForm(xml->getActualArch(), this);
    connect(sf, SIGNAL(reportSent(Report*)),this, SLOT(reportSent(Report*)));

    sf->show();
}

void ManagerGui::startUp() {
    //Starting function.

    xml = new XmlModule;                            //Interface to xml file.

    QList<Report*> *reports = xml->getReports();    //Retrieve a pointer list to the reports.
    model = new TablesModel(reports);               //Init table model.

    notSentProxy = new CustomTableProxy(false);
    sentProxy = new CustomTableProxy(true);

    notSentProxy->setDynamicSortFilter(true);
    sentProxy->setDynamicSortFilter(true);

    sentProxy->setSourceModel(model);
    notSentProxy->setSourceModel(model);

    ui->notSentTable->setModel(notSentProxy);
    ui->sentTable->setModel(sentProxy);
}

void ManagerGui::notSentDoubleClicked ( const QModelIndex & index ) {
    //SLOT: Catches the double clicks from the notSent table.

    QModelIndex realIndex = notSentProxy->mapToSource(index);
    Report *selectedReport = model->getReport(realIndex);

    ViewReport *viewReport = new ViewReport(selectedReport->getTextualDescription());
    viewReport->show();
}

void ManagerGui::sentDoubleClicked ( const QModelIndex & index ) {
    //SLOT: Catches the double clicks from the sent table.

    QModelIndex realIndex = sentProxy->mapToSource(index);
    Report *selectedReport = model->getReport(realIndex);

    ViewReport *viewReport = new ViewReport(selectedReport->getTextualDescription());
    viewReport->show();
}

TablesModel* ManagerGui::getDataModel() {
    return model;
}

void ManagerGui::reportSent(Report* sentReport) {
    //SLOT: sets the "sent" flag of the just sent report and invalidates the proxy filter updating the tableviews.

    sentReport->setSent(true);

    xml->save(); //The changes are saved on file.

    //Invalidation of proxies filter for tableview update.
    notSentProxy->invalidate();
    sentProxy->invalidate();
}




