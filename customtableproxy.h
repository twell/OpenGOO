#ifndef CUSTOMTABLEPROXY_H
#define CUSTOMTABLEPROXY_H

#include <QSortFilterProxyModel>

class CustomTableProxy : public QSortFilterProxyModel
{
    bool sended;

public:
    CustomTableProxy(bool sended); //The flag initializes the proxy class in sended table mode or unsended table mode.

    bool filterAcceptsColumn ( int source_column, const QModelIndex & source_parent ) const; //Reimplemented.
    bool filterAcceptsRow ( int source_row, const QModelIndex & source_parent ) const;       //Reimplemented.
};

#endif // CUSTOMTABLEPROXY_H
