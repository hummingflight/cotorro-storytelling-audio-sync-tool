#include "ctSfmlCanvas.h"

#ifdef Q_WS_X11
    #include <Qt/qx11info_x11.h>
    #include <X11/Xlib.h>
#endif


namespace ct {

SfmlCanvas::SfmlCanvas
(
    QWidget *parent,
    const QPoint& _position,
    const QSize& _size,
    quint32 _frameTime
) :
  QWidget(parent),
  _m_isReady(false),
  _m_timer(),  
  _m_clock()
{
  // Setup some states to allow direct rendering into the widget
  setAttribute(Qt::WA_PaintOnScreen);
  setAttribute(Qt::WA_OpaquePaintEvent);
  setAttribute(Qt::WA_NoSystemBackground);

  // Set strong focus to enable keyboard events to be received
  setFocusPolicy(Qt::StrongFocus);

  // Setup the widget geometry
  move(_position);
  resize(_size);

  sf::RenderWindow::setVerticalSyncEnabled(true);
  sf::RenderWindow::setFramerateLimit(60);

  // Setup the timer
  _m_timer.setInterval(_frameTime);
  _m_clock.restart();

  return;
}

SfmlCanvas::~SfmlCanvas()
{
  _m_timer.stop();
  return;
}

sf::Time
SfmlCanvas::getDeltaTime()
{
  return _m_deltaTime;
}

void
SfmlCanvas::onTimeOut()
{
  // Run redrawing.
  QWidget::repaint();
  return;
}

QPaintEngine*
SfmlCanvas::paintEngine() const
{
  return nullptr;
}

void
SfmlCanvas::showEvent(QShowEvent*)
{
  if(!_m_isReady) {

    // Under X11, we need to flush the commands sent to the server to ensure that
    // SFML will get an updated view of the windows
    #ifdef Q_WS_X11
      XFlush(QX11Info::display());
    #endif

    // Create the SFML window with the widget handle
    sf::RenderWindow::create(reinterpret_cast<sf::WindowHandle>(QWidget::winId()));

    // Let the derived class do its specific stuff
    onInit();

    // Setup the timer to trigger a refresh at specified frame rate
    connect(&_m_timer, &QTimer::timeout, this, &SfmlCanvas::onTimeOut);
    _m_timer.start();

    _m_isReady = true;
  }

  return;
}

void
SfmlCanvas::paintEvent(QPaintEvent *)
{
  // Delta time.
  _m_deltaTime = _m_clock.restart();

  // Update callback.
  onUpdate();

  // Display the rendered window.
  sf::RenderWindow::display();

  return;
}

}


