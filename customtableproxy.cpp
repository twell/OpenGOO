#include "customtableproxy.h"

CustomTableProxy::CustomTableProxy(bool sended)
{
    this->sended = sended;
}

bool CustomTableProxy::filterAcceptsColumn ( int source_column, const QModelIndex & source_parent ) const {
    //Filters the columns from the model.

    Q_UNUSED(source_parent);
    if(sended == true) { //SendedTable Columns.

        if(source_column == 0 ||  source_column == 1 ||source_column == 2 || source_column == 3 || source_column == 4)
            return true;

    } else { //UnsendedTable Columns.

        if(source_column == 0 ||  source_column == 1)
            return true;
    }

    return false;
}

bool CustomTableProxy::filterAcceptsRow ( int source_row, const QModelIndex & source_parent ) const {
    //Filters the rows checking the sended column.

    QModelIndex index = sourceModel()->index(source_row, 5, source_parent);

    if(sended == true) { //SendedTable filter.

        if(sourceModel()->data(index).toString().compare("true") == 0)
            return true;

    } else { //UnsendedTable filter.

        if(sourceModel()->data(index).toString().compare("false") == 0)
            return true;
    }

    return false;
}
