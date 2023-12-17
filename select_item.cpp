#include "select_item.h"
#include "mytree.h"

#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include <qDebug>
#include <QScrollBar>
#include <QHeaderView>
#include <QTreeWidgetItem>

select_item::select_item(QWidget *parent)
    : QWidget{parent}{

}

void select_item::CreateTop(){

    ItemTree = new mytree();

    QTreeWidgetItem *ClockItem =new QTreeWidgetItem();
    ClockItem->setText(0,"Clock Set Flow");
    QTreeWidgetItem *ClockChild = new QTreeWidgetItem(ClockItem);
    ClockChild->setIcon(0,QIcon(":/new/resource/res/clock.png"));
    ClockChild->setText(0,"Set Clock");
    ItemTree->addTopLevelItem(ClockItem);
    ClockItem->setExpanded(true);

    QTreeWidgetItem *PowerItem =new QTreeWidgetItem();
    PowerItem->setText(0,"Power Set Flow");
    QTreeWidgetItem *PowerChild = new QTreeWidgetItem(PowerItem);
    PowerChild->setIcon(0,QIcon(":/new/resource/res/clock.png"));
    PowerChild->setText(0,"Set Power");
    ItemTree->addTopLevelItem(PowerItem);
    PowerItem->setExpanded(true);

    QTreeWidgetItem *ControlItem =new QTreeWidgetItem();
    ControlItem->setText(0,"Control Set Flow");
    QTreeWidgetItem *ResetChild = new QTreeWidgetItem(ControlItem);
    ResetChild->setIcon(0,QIcon(":/new/resource/res/clock.png"));
    ResetChild->setText(0,"Set Reset");
    QTreeWidgetItem *DeResetChild = new QTreeWidgetItem(ControlItem);
    DeResetChild->setIcon(0,QIcon(":/new/resource/res/clock.png"));
    DeResetChild->setText(0,"Set DeReset");
    QTreeWidgetItem *ControlChild = new QTreeWidgetItem(ControlItem);
    ControlChild->setIcon(0,QIcon(":/new/resource/res/clock.png"));
    ControlChild->setText(0,"Set Control");
    ItemTree->addTopLevelItem(ControlItem);
    ControlItem->setExpanded(true);

    QTreeWidgetItem *ProgressItem =new QTreeWidgetItem();
    ProgressItem->setText(0,"Program Set Flow");
    QTreeWidgetItem *ProgramItem = new QTreeWidgetItem(ProgressItem);
    ProgramItem->setIcon(0,QIcon(":/new/resource/res/clock.png"));
    ProgramItem->setText(0,"Set TestCase");
    ItemTree->addTopLevelItem(ProgressItem);
    ProgressItem->setExpanded(true);

    ItemTree->setObjectName("TreeMenu");
    ItemTree->verticalScrollBar()->setObjectName("TreeMenuVerticl");
    ItemTree->horizontalScrollBar()->setObjectName("TreeMenuHorizontal");

    ItemTree->setColumnCount(1);
    ItemTree->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    ItemTree->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    ItemTree->setAutoScroll(true);
    ItemTree->header()->setVisible(false);

    ItemTree->setFrameStyle(QFrame::Sunken);
    ItemTree->setAnimated(true);

    ItemTree->setStyleSheet("QTreeView::item { margin-top: 3px; margin-bottom: 2px; }");

    ItemDock->clear();
    ItemDock->addTab(ItemTree,"Project View");

}



