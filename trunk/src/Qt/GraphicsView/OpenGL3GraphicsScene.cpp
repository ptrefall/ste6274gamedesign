#include "OpenGL3GraphicsScene.h"
#include <Qt/UserInterface/MainMenu.h>
#include <Game/Game.h>

#include <GL/glew.h>
#include <GL/wglew.h>
#include <QtGui>
#include <QtOpenGL>

QDialog *OpenGL3GraphicsScene::createDialog(const QString &windowTitle) const
{
    QDialog *dialog = new QDialog(0, Qt::CustomizeWindowHint | Qt::WindowTitleHint);

    dialog->setWindowOpacity(0.8);
    dialog->setWindowTitle(windowTitle);
    dialog->setLayout(new QVBoxLayout);

    return dialog;
}

OpenGL3GraphicsScene::OpenGL3GraphicsScene(Game &game)
    : game(game), m_backgroundColor(0, 170, 255), first_time(true)
{
    QWidget *controls = createDialog(tr("Controls"));

    QPushButton *backgroundButton = new QPushButton(tr("Choose background color"));
    connect(backgroundButton, SIGNAL(clicked()), this, SLOT(setBackgroundColor()));
    controls->layout()->addWidget(backgroundButton);

    QWidget *instructions = createDialog(tr("Instructions"));
    instructions->layout()->addWidget(new QLabel(tr("Use mouse wheel to zoom model, and click and drag to rotate model")));
    instructions->layout()->addWidget(new QLabel(tr("Move the sun around to change the light position")));

    addWidget(instructions);
    addWidget(controls);
	MainMenu *menu = new MainMenu();
	addWidget(menu);

    QPointF pos(10, 10);
    foreach (QGraphicsItem *item, items()) {
        item->setFlag(QGraphicsItem::ItemIsMovable);
        item->setCacheMode(QGraphicsItem::DeviceCoordinateCache);

        const QRectF rect = item->boundingRect();
        item->setPos(pos.x() - rect.x(), pos.y() - rect.y());
        pos += QPointF(0, 10 + rect.height());
    }

    QRadialGradient gradient(40, 40, 40, 40, 40);
    gradient.setColorAt(0.2, Qt::yellow);
    gradient.setColorAt(1, Qt::transparent);

    m_lightItem = new QGraphicsRectItem(0, 0, 80, 80);
    m_lightItem->setPen(Qt::NoPen);
    m_lightItem->setBrush(gradient);
    m_lightItem->setFlag(QGraphicsItem::ItemIsMovable);
    m_lightItem->setPos(800, 200);
    addItem(m_lightItem);

    m_time.start();
}

void OpenGL3GraphicsScene::drawBackground(QPainter *painter, const QRectF &)
{
    if (painter->paintEngine()->type() != QPaintEngine::OpenGL2) {
        qWarning("OpenGL3GraphicsScene: drawBackground needs a QGLWidget to be set as viewport on the graphics view");
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
		} catch(T_Exception &/*e*/){
			//std::cout << e.what() << std::endl;
		}
		first_time = false;
	}

    glClearColor(m_backgroundColor.redF(), m_backgroundColor.greenF(), m_backgroundColor.blueF(), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//We'll have to deal with some OpenGl2 compatibility in order to keep Qt's paint engine happy :P
	glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluPerspective(70, width() / height(), 0.01, 1000);

	glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

	//////////////////////////////
	const S32 delta = m_time.elapsed() - m_lastTime;
	m_lastTime += delta;

	game.advanceFrame((F32)delta/1000.0f);
	//////////////////////////////

	glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    QTimer::singleShot(1/60*1000+1, this, SLOT(update()));
}

void OpenGL3GraphicsScene::setBackgroundColor()
{
    const QColor color = QColorDialog::getColor(m_backgroundColor);
    if (color.isValid()) {
        m_backgroundColor = color;
        //update();
    }
}

void OpenGL3GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
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

void OpenGL3GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);
    if (event->isAccepted())
        return;

    m_mouseEventTime = m_time.elapsed();
    event->accept();
}

void OpenGL3GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);
    if (event->isAccepted())
        return;

    const int delta = m_time.elapsed() - m_mouseEventTime;
    event->accept();
    //update();
}

void OpenGL3GraphicsScene::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    QGraphicsScene::wheelEvent(event);
    if (event->isAccepted())
        return;

    event->accept();
    //update();
}
