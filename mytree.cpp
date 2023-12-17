#include "mytree.h"
#include <QMimeData>

mytree::mytree(QWidget *parent):QTreeWidget(parent){
    init();
}

void mytree::init(){

    m_label = new QLabel(this);
    m_label->resize(100,50);
    m_label->hide();
}

void mytree::mousePressEvent(QMouseEvent *event){

    m_selectItem = static_cast<QTreeWidgetItem*>(this->itemAt(event->pos()));

    if ((event->button()==Qt::LeftButton&&m_selectItem) && m_selectItem->parent()!=NULL){

        QByteArray dataItem;
        QDataStream dataStream(&dataItem, QIODevice::WriteOnly);
        dataStream << m_selectItem->text(0);
        m_label->setText(m_selectItem->text(0));

        //设置自定义数据
        QMimeData* mimeData = new QMimeData;
        mimeData->setData("Data/name", dataItem);

        //拖动设置
        QDrag* drag = new QDrag(this);
        drag->setPixmap(m_label->grab());
        drag->setMimeData(mimeData);
        drag->setHotSpot(QPoint(0,0));
        drag->exec();

//               Qt::DropAction dropAction = drag->exec(Qt::MoveAction|Qt::CopyAction,Qt::CopyAction);
//                if(dropAction == Qt::MoveAction)
//                {
//                    //当成功拖动时清除原节点
//                    delete m_selectItem;
//                    m_selectItem = NULL;
//                    //qDebug()<<"成功";
//                }

    }

    QTreeWidget::mousePressEvent(event);

}
