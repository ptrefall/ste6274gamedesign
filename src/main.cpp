
#include <types_config.h>
#include "Qt/GraphicsView/OpenGL3GraphicsScene.h"
#include "Game/game.h"

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

	Game game;
	game.initialize();
 
    //assigning that scene to the view
    GraphicsView view;
	
	QGLFormat format( QGL::AlphaChannel | QGL::DoubleBuffer | QGL::DepthBuffer | QGL::Rgba | QGL::SampleBuffers | QGL::StereoBuffers );
	format.setProfile(QGLFormat::CompatibilityProfile); //Have to run in compatibility mode, because of Qt's PaintEngine working with GraphicsView is GL2...
    format.setVersion(3,3);
	
	QGLWidget *glWidget = new QGLWidget(format);
	view.setViewport(glWidget);
    view.setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

	view.setScene(new OpenGL3GraphicsScene(game));
    view.show();
	view.resize(1024, 768);

    return app.exec();
}