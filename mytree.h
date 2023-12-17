#ifndef MYTREE_H
#define MYTREE_H

#include <QTreeWidget>
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QTreeWidgetItem>
#include <QMouseEvent>
#include <QDrag>

class mytree : public QTreeWidget
{
    Q_OBJECT
public:
    explicit mytree(QWidget *parent = nullptr);

    void init();
    void mousePressEvent(QMouseEvent *even);

public:

    QLabel *m_label;
    QTreeWidgetItem *m_selectItem;

};

#endif // MYTREE_H
