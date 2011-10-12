
#include <types_config.h>
#include "Qt/GraphicsView/OpenGL2GraphicsScene.h"
#include "Game/game.h"

#include <QtGui>
#include <QtOpenGL\qgl.h>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QHostAddress>

#include <Protocol/gameprotocol.h>
/*#include "Qt/Client/DataPacket.h"
#include "Qt/Client/RequestInfo.h"
#include "Qt/Client/ParsedData.h"*/

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
	// Register game protocol types as meta types
	qRegisterMetaType<gp_connect_request>( "gp_connect_request" );
	qRegisterMetaType<gp_default_server_query>( "gp_default_server_query" );
	qRegisterMetaType<gp_join_request>( "gp_join_request" );
	qRegisterMetaType<gp_client_verification_answer>("gp_client_verification_answer");
	qRegisterMetaType<QHostAddress>( "QHostAddress" );

	// Register local non-QObject types as meta types
	//qRegisterMetaType<RequestInfo> ("RequestInfo");
	//qRegisterMetaType<ParsedData> ("ParsedData");

    QApplication app(argc, argv);

	Game game;
	game.initializeCore();
 
    //assigning that scene to the view
    GraphicsView view;
	
	QGLFormat format( QGL::AlphaChannel | QGL::DoubleBuffer | QGL::DepthBuffer | QGL::Rgba | QGL::SampleBuffers | QGL::StereoBuffers );
	format.setProfile(QGLFormat::CompatibilityProfile); //Have to run in compatibility mode, because of Qt's PaintEngine working with GraphicsView is GL2...
    format.setVersion(3,3);
	
	QGLWidget *glWidget = new QGLWidget(format);
	view.setViewport(glWidget);
    view.setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

	view.setScene(new OpenGL2GraphicsScene(game));
    view.show();
	view.resize(1024, 768);

	int result = app.exec();
    return result;
}