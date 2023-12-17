#include "diagramPixmapItemEdit.h"

#include <QPixmap>
#include <iostream>
#include <QDebug>
#include <QApplication>
#include <QDrag>
#include <QMimeData>

DiagramPixmapItemEdit::DiagramPixmapItemEdit()
{
}
/*note: imagesize = 80 is in the DiagramPixmapItemEdit.h*/
DiagramPixmapItemEdit::DiagramPixmapItemEdit(QString file,QString text,QSize imagesize)
{
    setMyText(text);
    setMyPixmap(file,imagesize);
    setCursor(Qt::OpenHandCursor);
    setAcceptedMouseButtons(Qt::LeftButton);

//    setFlag(QGraphicsItem::ItemIsMovable, false);
//    setFlag(QGraphicsItem::ItemIsSelectable, false);
//    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
   // setAcceptHoverEvents(true);
}

void DiagramPixmapItemEdit::setMyText(QString &text)
{
    myText = text;
}

void DiagramPixmapItemEdit::setMyPixmap(QString &file,QSize size)
{
    //myImage = file;
    QPixmap pixmap;
    pixmap.load(file);
    pixmap= pixmap.scaled(size.width(),size.height()-textHeight,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    setPixmap(pixmap);
}
QRectF DiagramPixmapItemEdit::boundingRect() const
{
    QRect rect = this->pixmap().rect();
    //return QRectF(rect);
    return QRectF(0,0,rect.width(),rect.height()+textHeight);
}

void DiagramPixmapItemEdit::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pixmap = this->pixmap();
    QRect rect = this->pixmap().rect();

    painter->drawPixmap(rect,pixmap);


    //print name,calculate the text's heigh & width for center layout
    QPen pen(Qt::black);
    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing);
    QFont font("\"思源黑体 CN bold\",\"思源黑体 CN\"",17, QFont::Normal);
    painter->setFont(font);
    painter->drawText(QRectF(0,rect.height(),rect.width(),textHeight),Qt::AlignCenter,myText);

    if (option->state & QStyle::State_Sunken)
    {
        QRectF rect1 = boundingRect();
        //QPen pen(Qt::darkGreen);
        painter->setPen(QPen(Qt::darkGreen));
    }else
    {

    }
}

int DiagramPixmapItemEdit::getTextHeight()
{
    return textHeight;
}

QPainterPath DiagramPixmapItemEdit::shape() const
{
    QRectF rect = boundingRect();

    QPainterPath path;
    path.addRoundRect(rect, 5,5);
    return path;
}

void DiagramPixmapItemEdit::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(Qt::ClosedHandCursor);
    //emit nodeIsPressed();
    qDebug()<<"pressed";
   // QGraphicsItem::mousePressEvent(event);
}
void DiagramPixmapItemEdit::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<"release";
    setCursor(Qt::OpenHandCursor);
    update(boundingRect());
   // QGraphicsItem::mouseReleaseEvent(event);
}
void DiagramPixmapItemEdit::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<"move";
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
            .length() < QApplication::startDragDistance()) {
        return;
    }

    QDrag *drag = new QDrag(event->widget());
    QMimeData *mime = new QMimeData;
    drag->setMimeData(mime);


    QPixmap pix = this->pixmap();
    mime->setImageData(pix);

    drag->setPixmap(pix);
    drag->setHotSpot(QPoint(pix.width()-7, pix.height()-7));

    drag->exec();
    setCursor(Qt::OpenHandCursor);
}

QString DiagramPixmapItemEdit::getMyText()
{
    return myText;
}
