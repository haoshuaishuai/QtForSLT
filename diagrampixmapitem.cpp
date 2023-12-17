#include "diagrampixmapitem.h"
#include "diagramscene.h"

#include <QPixmap>
#include <iostream>
#include <QDebug>
#include <QApplication>
#include <QDrag>
#include <QMimeData>
#include <QGraphicsScene>
#include <QTextDocument>
#include <QGraphicsPixmapItem>
#include <QPainterPath>

DiagramPixmapItem::DiagramPixmapItem(QString file,QSize imagesize,bool isMovable){

    if(isMovable){
        setFlag(ItemIsMovable);
    }

    setFlag(QGraphicsItem::ItemIsSelectable, true);

    //set center text
    textItem = new SingleLineTextItem("", this);
    if(imagesize.width()!=180){
        textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
        textItem->setFlag(QGraphicsItem::ItemIsSelectable);
        textItem->setFlag(QGraphicsItem::ItemIsFocusable);
    }
    textItem->setPos(0, 0);
    textItem->setDefaultTextColor(Qt::black);
    QTextDocument *doc = textItem->document();
    connect(doc, &QTextDocument::contentsChanged, [=]{
        updateTextItemAlignment();
    });

    //set pixmap
    pixmap.load(file);
    pixmap= pixmap.scaled(imagesize.width(),imagesize.height(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    setPixmap(pixmap);

    //set text is the pixmap center
    QRectF pixmapRect = this->boundingRect();
    QRectF textRect = textItem->boundingRect();
    qreal centerX = (pixmapRect.width() - textRect.width()) / 2;
    qreal centerY = (pixmapRect.height() - textRect.height()) / 2;
    textItem->setPos(centerX,centerY);

}

void DiagramPixmapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    QGraphicsPixmapItem::paint(painter, option, widget);

}

void DiagramPixmapItem::updateTextItemAlignment() {

    QRectF textRect = textItem->boundingRect();
    QRectF pixmapRect = this->boundingRect();
    qreal newX = pixmapRect.width() / 2.0 - textRect.width() / 2.0;
    qreal newY = pixmapRect.height() / 2.0 - textRect.height() / 2.0;
    textItem->setPos(newX, newY);

}

void DiagramPixmapItem::setText(const QString& text){

    textItem->setPlainText(text);

}

QVariant DiagramPixmapItem::itemChange(GraphicsItemChange change, const QVariant& value){

    //item select
    if (change == ItemSelectedChange && scene()) {

        if (value.toBool()) {
            textItem->setFocus(Qt::MouseFocusReason);
        } else {
            textItem->clearFocus();
        }

    }

    //item moved
    /*if (change == QGraphicsItem::ItemPositionChange && scene()) {

        qDebug()<<"heloo2222";
        QPointF newPos = value.toPointF();
        emit itemMoved(newPos);

    }*/

    return QGraphicsItem::itemChange(change, value);


}


void DiagramPixmapItem::keyPressEvent(QKeyEvent* event){



}

void DiagramPixmapItem:: mousePressEvent(QGraphicsSceneMouseEvent *event){

    QGraphicsPixmapItem::mousePressEvent(event);
    if (isSelected()){
        textItem->clearFocus();
    }

}
