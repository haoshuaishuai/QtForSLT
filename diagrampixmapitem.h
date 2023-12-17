#ifndef DIAGRAMPIXMAPITEM_H
#define DIAGRAMPIXMAPITEM_H


#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QTextOption>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include <QKeyEvent>

class SingleLineTextItem : public QGraphicsTextItem{

public:

    SingleLineTextItem(const QString& text, QGraphicsItem* parent = nullptr):QGraphicsTextItem(text, parent){


    }

protected:

    void keyPressEvent(QKeyEvent *event) override{

        if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return){
            event->ignore();
        }
        else{
            QGraphicsTextItem::keyPressEvent(event);
        }
    }

};

class DiagramPixmapItem : public QObject,public QGraphicsPixmapItem{

    Q_OBJECT

public:

    DiagramPixmapItem(QString file,QSize imagesize,bool isMovable);

    void setText(const QString& text);

    void updateTextItemAlignment();

public:

    SingleLineTextItem *textItem;

    QPixmap pixmap;

public:

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void keyPressEvent(QKeyEvent* event) override;

signals:
    void itemMoved(const QPointF& newPos);

};


#endif // DIAGRAMPIXMAPITEM_H
