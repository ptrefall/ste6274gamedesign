#include "OpenGL2GraphicsScene.h"
#include <Qt/UserInterface/MainMenu.h>
#include <Game/Game.h>

#include <GL/glew.h>
#include <GL/wglew.h>
#include <QtGui>
#include <QtOpenGL>

#include <iostream>

QDialog *OpenGL2GraphicsScene::createDialog(const QString &windowTitle) const
{
    QDialog *dialog = new QDialog(0, Qt::CustomizeWindowHint | Qt::WindowTitleHint);

    dialog->setWindowOpacity(0.8);
    dialog->setWindowTitle(windowTitle);
    dialog->setLayout(new QVBoxLayout);

    return dialog;
}

OpenGL2GraphicsScene::OpenGL2GraphicsScene(Game &game)
    : game(game), m_backgroundColor(0, 170, 255), first_time(true)
{
    /*QWidget *controls = createDialog(tr("Controls"));

    QPushButton *backgroundButton = new QPushButton(tr("Choose background color"));
    connect(backgroundButton, SIGNAL(clicked()), this, SLOT(setBackgroundColor()));
    controls->layout()->addWidget(backgroundButton);

    QWidget *instructions = createDialog(tr("Instructions"));
    instructions->layout()->addWidget(new QLabel(tr("Use mouse wheel to zoom model, and click and drag to rotate model")));
    instructions->layout()->addWidget(new QLabel(tr("Move the sun around to change the light position")));

    addWidget(instructions);
    addWidget(controls);*/
	Ui::MainMenu *menu = new Ui::MainMenu(this, game);
	//menu->move(this->sceneRect().center().toPoint());
	addWidget(menu);
	

	QPointF pos(this->sceneRect().center().x()/2 - menu->geometry().width()/4, this->sceneRect().center().y()/2 - menu->geometry().width());
    foreach (QGraphicsItem *item, items()) {
        item->setFlag(QGraphicsItem::ItemIsMovable);
        item->setCacheMode(QGraphicsItem::DeviceCoordinateCache);

        const QRectF rect = item->boundingRect();
        item->setPos(pos.x(), pos.y());
    }

    /*QRadialGradient gradient(40, 40, 40, 40, 40);
    gradient.setColorAt(0.2, Qt::yellow);
    gradient.setColorAt(1, Qt::transparent);

    m_lightItem = new QGraphicsRectItem(0, 0, 80, 80);
    m_lightItem->setPen(Qt::NoPen);
    m_lightItem->setBrush(gradient);
    m_lightItem->setFlag(QGraphicsItem::ItemIsMovable);
    m_lightItem->setPos(800, 200);
    addItem(m_lightItem);*/

    m_time.start();
}

void OpenGL2GraphicsScene::drawBackground(QPainter *painter, const QRectF &)
{
    if (painter->paintEngine()->type() != QPaintEngine::OpenGL2) {
        qWarning("OpenGL2GraphicsScene: drawBackground needs a QGLWidget to be set as viewport on the graphics view");
        return;
    }

	if(first_time)
	{
		try
		{
			glewExperimental = GL_TRUE;
			GLenum err = glewInit();
			if(err != GLEW_OK)
				throw T_Exception((const char *)glewGetErrorString(err));

			game.initializeGame();
		} catch(T_Exception &e){
			std::cout << e.what() << std::endl;
			system("pause");
			QApplication::quit();
		}
		first_time = false;
	}

    glClearColor(m_backgroundColor.redF(), m_backgroundColor.greenF(), m_backgroundColor.blueF(), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//We'll have to deal with some OpenGl2 compatibility in order to keep Qt's paint engine happy :P
	glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluPerspective(70, (float)width() / (float)height(), 1, 100000);

	glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

	//////////////////////////////
	const S32 delta = m_time.elapsed() - m_lastTime;
	m_lastTime += delta;
	//painter->beginNativePainting();
	game.advanceFrame((F32)delta/1000.0f);
	//painter->endNativePainting();
	//////////////////////////////

	glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    QTimer::singleShot(int(1.0f/60.0f*1000.0f)+1, this, SLOT(update()));
}

void OpenGL2GraphicsScene::setBackgroundColor()
{
    const QColor color = QColorDialog::getColor(m_backgroundColor);
    if (color.isValid()) {
        m_backgroundColor = color;
        //update();
    }
}

void OpenGL2GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
    if (event->isAccepted())
        return;
    if (event->buttons() & Qt::LeftButton) {
        const QPointF delta = event->scenePos() - event->lastScenePos();

        event->accept();
        //update();
    }
}

void OpenGL2GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);
    if (event->isAccepted())
        return;

    m_mouseEventTime = m_time.elapsed();
    event->accept();
}

void OpenGL2GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);
    if (event->isAccepted())
        return;

    const int delta = m_time.elapsed() - m_mouseEventTime;
    event->accept();
    //update();
}

void OpenGL2GraphicsScene::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    QGraphicsScene::wheelEvent(event);
    if (event->isAccepted())
        return;

    event->accept();
    //update();
}
