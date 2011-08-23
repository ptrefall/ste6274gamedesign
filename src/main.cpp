
#include "GraphicsView/OpenGL3GraphicsScene.h"
#include <QtGui>
#include <QtOpenGL\qgl.h>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>

class GraphicsView : public QGraphicsView
{
public:
    GraphicsView()
    {
        setWindowTitle(tr("Hello world!"));
    }

protected:
    void resizeEvent(QResizeEvent *event) {
        if (scene())
            scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
        QGraphicsView::resizeEvent(event);
    }
};

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
 
    //assigning that scene to the view
    GraphicsView view;
	view.setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
    view.setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
	view.setScene(new OpenGL3GraphicsScene());
    view.show();
	view.resize(1024, 768);

    return app.exec();
}