
#include "types.h"
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
	QGLFormat format( QGL::AlphaChannel | QGL::DoubleBuffer | QGL::DepthBuffer | QGL::Rgba | QGL::SampleBuffers | QGL::StereoBuffers );
	format.setProfile(QGLFormat::CompatibilityProfile); //Have to run in compatibility mode, because of Qt's PaintEngine working with GraphicsView...
    format.setVersion(3,3);
	QGLWidget *glWidget = new QGLWidget(format);
	view.setViewport(glWidget);
    view.setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

	try{
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if(err != GLEW_OK)
		throw T_Exception((const char *)glewGetErrorString(err));
	} catch(T_Exception &e){
		std::cout << e.what() << std::endl;
	}

	view.setScene(new OpenGL3GraphicsScene());
    view.show();
	view.resize(1024, 768);

    return app.exec();
}