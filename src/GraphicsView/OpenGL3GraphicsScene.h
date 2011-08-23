#pragma once

#include "types.h"
#include <QGraphicsScene>
#include <QLabel>
#include <QTime>

class OpenGL3GraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    OpenGL3GraphicsScene();

    void drawBackground(QPainter *painter, const QRectF &rect);

public slots:
    void setBackgroundColor();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void wheelEvent(QGraphicsSceneWheelEvent * wheelEvent);

private:
    QDialog *createDialog(const QString &windowTitle) const;

    QColor m_backgroundColor;

    QTime m_time;
    int m_lastTime;
    int m_mouseEventTime;

    QGraphicsRectItem *m_lightItem;
};
