#ifndef DIAGRAMPIXMAPITEMEDIT_H
#define DIAGRAMPIXMAPITEMEDIT_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>

class DiagramPixmapItemEdit : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    DiagramPixmapItemEdit();
    DiagramPixmapItemEdit(QString file,QString text,QSize imagesize=QSize(80,80));

    //setup function
    void setMyPixmap(QString &file,QSize size);
    void setMyText(QString &text);
    QString getMyText();
    //virtual function
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int getTextHeight();      //返回文本高度
signals:
    void nodeIsMoving(QPointF &pos);
    void nodeIsPressed();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
    //QString myImage;
    QString myText;
    int textHeight = 30;        //文本高度
};


#endif // DIAGRAMPIXMAPITEM_H
