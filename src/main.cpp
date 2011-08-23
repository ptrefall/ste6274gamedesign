
#include <QtGui/QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

	// making a scene on the application
    QGraphicsScene scene;
 
    //adding some text to the scene
    scene.addText("Hello, world!", QFont("Times", 20, QFont::Bold));
 
    //assigning that scene to the view
    QGraphicsView view(&scene);
    view.show();

    return app.exec();
}