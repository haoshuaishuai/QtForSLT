#ifndef SELECT_ITEM_H
#define SELECT_ITEM_H

#include <QObject>
#include <QWidget>
#include <QTreeWidget>
#include <QDockWidget>
#include <QTabWidget>

class select_item : public QWidget
{
    Q_OBJECT
public:
    explicit select_item(QWidget *parent = nullptr);

    QTabWidget * ItemDock;
    QTreeWidget * ItemTree;



public:

    void CreateTop();

signals:

};

#endif // SELECT_ITEM_H
