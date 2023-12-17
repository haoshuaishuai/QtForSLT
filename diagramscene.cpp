#include "diagramscene.h"
#include "diagrampixmapitem.h"
#include "arrow.h"

#include <QTextCursor>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QMimeData>
#include <QSize>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <QDebug>
#include <QList>
#include <QDebug>


DiagramScene::DiagramScene(QObject *parent) : QGraphicsScene(parent){

    pixmapItems = new QList<DiagramPixmapItem*>();

    arrowItems = new QList<arrow*>();

    //add start Item
    startItem = new DiagramPixmapItem(":/items/resource/icon-connect.png",QSize(250,60),false);
    pixmapItems->append(startItem);
    startItem->setPos(100, 500);
    this->addItem(startItem);

    //add End Item
    EndItem = new DiagramPixmapItem(":/items/resource/icon-export.png",QSize(250,60),false);
    EndItem->setPos(startItem->pos().x(), startItem->pos().y() + startItem->boundingRect().height());
    pixmapItems->append(EndItem);
    this->addItem(EndItem);

    //only select one item
    connect(this, &QGraphicsScene::selectionChanged, this, &DiagramScene::handleSelectionChanged);


}

void DiagramScene::handleSelectionChanged() {

    QList<QGraphicsItem*> selectedItems = this->selectedItems();
    if (selectedItems.size() > 1) {
        for (int i=0; i<selectedItems.size()-1; ++i) {
            selectedItems[i]->setSelected(false);
        }
    }

}

void DiagramScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event){

    event->accept();

}

void DiagramScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event){

    event->accept();
    QGraphicsScene::dragEnterEvent(event);

}

void DiagramScene::dropEvent(QGraphicsSceneDragDropEvent *event){

    if (event->mimeData()->hasFormat("Data/name")){

        //get tree item
        QByteArray itemData = event->mimeData()->data("Data/name");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);
        QString text;
        dataStream >> text;

        //create new DiagramPixmapItem
        DiagramPixmapItem* item = new DiagramPixmapItem(":/items/resource/icon-delect.png",QSize(250,60),true);

        item->setText(text);

        //get mouse pos
        QPointF mousePos = event->scenePos();

        //calcu min distance
        qreal minDistance = std::numeric_limits<qreal>::max();
        DiagramPixmapItem* closestItem = nullptr;
        int next = 0;

        //get nerest item
        for(int i = 0;i<pixmapItems->size();i++){

            DiagramPixmapItem* item = pixmapItems->at(i);
            QPointF itemPos = item->pos();
            itemPos.setY(itemPos.y()+item->boundingRect().height());
            qreal distance = QLineF(mousePos, itemPos).length();
            if (distance < minDistance){
                minDistance = distance;
                closestItem = item;
                next = i+1;
            }

        }

        //if closesItem is End next minus 1
        if(next == pixmapItems->size()){
            closestItem = pixmapItems->at(next-2);
            next--;
        }

        //move other items
        if(next < pixmapItems->size()){
            for(int i = next;i<pixmapItems->size();i++){
                DiagramPixmapItem* it = pixmapItems->at(i);
                it->setPos(closestItem->pos().x(), closestItem->pos().y() + (closestItem->boundingRect().height()+40)*(i-next+2));
            }
        }

        //insert a new item
        if (closestItem){
            pixmapItems->insert(next,item);
            item->setPos(closestItem->pos().x(), closestItem->pos().y() + closestItem->boundingRect().height()+40);
            this->addItem(item);
        }else{
            pixmapItems->append(item);
            item->setPos(100, 50);
            this->addItem(item);
        }

        addarrow();

    }

    this->update();

    QGraphicsScene::dropEvent(event);

}

void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *event){

    QPointF scenePos = event->scenePos();
    QList<QGraphicsItem*> selectItems = this->items(scenePos);

    for(int i = 0;i<pixmapItems->size();i++){

        pixmapItems->at(i)->setZValue(0);
        for(int j = 0;j<selectItems.size();j++){
            if(dynamic_cast<DiagramPixmapItem*>(selectItems.at(j))==pixmapItems->at(i)){
                pixmapItems->at(i)->setZValue(1);
               // qDebug()<<pixmapItems->at(i)->textItem->toPlainText()<<" set hou:"<<pixmapItems->at(i)->zValue();
            }
        }

    }

    for(int i = 0;i<pixmapItems->size();i++){

       // qDebug()<<pixmapItems->at(i)->textItem->toPlainText()<<":"<<pixmapItems->at(i)->zValue();

    }

    this->update();

    QGraphicsScene::mousePressEvent(event);

}


void DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){


    QPointF scenePos = event->scenePos();
    QList<QGraphicsItem*> selectItems = this->items(scenePos);
    if(selectItems.size()==0)
        return;

    //create new DiagramPixmapItem
    DiagramPixmapItem* item = dynamic_cast<DiagramPixmapItem*>(selectItems.at(0));
    //if item not DiagramPixmapItem
    if(item==NULL){
        item = dynamic_cast<DiagramPixmapItem*>(selectItems.at(1));
    }

    //get item pos
    int itempos = pixmapItems->size();
    for(int i = 0;i<pixmapItems->size();i++){

        DiagramPixmapItem* it = pixmapItems->at(i);
        if(item == it){
            itempos = i;
        }

    }

    //remove item
    pixmapItems->removeOne(item);

    //calcu min distance
    qreal minDistance = std::numeric_limits<qreal>::max();
    DiagramPixmapItem* closestItem = nullptr;
    int next = 0;

    //get nerest item
    for(int i = 0;i<pixmapItems->size();i++){

        DiagramPixmapItem* it = pixmapItems->at(i);
        QPointF itemPos = it->pos();
        itemPos.setY(itemPos.y()+it->boundingRect().height());
        qreal distance = QLineF(scenePos, itemPos).length();
        //qDebug()<<it->textItem->toPlainText()<<":"<<distance<<"scenePos:"<<scenePos<<"itemPos:"<<itemPos;
        if (distance < minDistance){
            minDistance = distance;
            closestItem = it;
            next = i+1;
        }

    }

    //if closesItem is End next minus 1
    if(next == pixmapItems->size()){
        closestItem = pixmapItems->at(next-2);
        next--;
    }

    //move other items up
    for(int i = 0;i<pixmapItems->size();i++){

        DiagramPixmapItem* it = pixmapItems->at(i);
        if(i>=itempos){
            it->setPos(it->pos().x(), it->pos().y() - (item->boundingRect().height()+40));
        }

    }

    //move other items down
    if(next < pixmapItems->size()){
        for(int i = next;i<pixmapItems->size();i++){

            DiagramPixmapItem* it = pixmapItems->at(i);
            it->setPos(closestItem->pos().x(), closestItem->pos().y() + (closestItem->boundingRect().height()+40)*(i-next+2));

        }
    }

    //insert a new item
    if (closestItem){
        pixmapItems->insert(next,item);
        item->setPos(closestItem->pos().x(), closestItem->pos().y() + closestItem->boundingRect().height()+40);
    }else{
        pixmapItems->append(item);
        item->setPos(100, 50);
    }

    addarrow();

    this->update();

    QGraphicsScene::mouseReleaseEvent(event);

}

void DiagramScene::addarrow(){

    arrowItems->clear();

    QList<QGraphicsItem*> items = this->items();
    for(int i = 0; i < items.size(); ++i){
        arrow* arrows = dynamic_cast<arrow*>(items[i]);
        if(arrows){
            delete arrows;
        }
    }

    for(int i = 0;i<pixmapItems->size()-1;i++){

        DiagramPixmapItem* item1 = pixmapItems->at(i);
        QPointF itemPos1 = item1->pos();
        itemPos1.setX(itemPos1.x()+item1->boundingRect().width()/2);
        itemPos1.setY(itemPos1.y()+item1->boundingRect().height());

        DiagramPixmapItem* item2 = pixmapItems->at(i+1);
        QPointF itemPos2 = item2->pos();
        itemPos2.setX(itemPos2.x()+item2->boundingRect().width()/2);
        itemPos2.setY(itemPos2.y());

        QLineF line(itemPos2, itemPos1);
        arrow *arrowitem = new arrow(line);
        arrowItems->append(arrowitem);
        this->addItem(arrowitem);

    }

}


