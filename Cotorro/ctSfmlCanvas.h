#ifndef SFMLCANVAS_H
#define SFMLCANVAS_H

#include <QWidget>
#include <QTimer>

#include <SFML/Graphics.hpp>

namespace ct {

/**
 * @brief The SfmlCanvas class
 */
class SfmlCanvas :
    public QWidget,
    public sf::RenderWindow
{
  Q_OBJECT
public:

  /**
   * @brief Constructor.
   *
   * @param _parent
   * @param _position
   * @param _size
   * @param _frameTime
   */
  explicit SfmlCanvas
  (
      QWidget* _parent,
      const QPoint& _position,
      const QSize& _size,
      quint32 _frameTime = 0
  );

  /**
   * @brief Destructor.
   */
  virtual ~SfmlCanvas();

signals:

private slots:

  void
  onTimeOut();

private:

  /**
   * @brief onInit
   */
  virtual void
  onInit() = 0;

  /**
   * @brief onUpdate
   */
  virtual void
  onUpdate() = 0;

  /**
   * @brief paintEngine
   * @return
   */
  virtual QPaintEngine*
  paintEngine() const override;

  /**
   * @brief showEvent
   */
  virtual void
  showEvent(QShowEvent*) override;

  /**
   * @brief paintEvent
   */
  virtual void
  paintEvent(QPaintEvent*) override;

  /**
   * @brief _m_timer
   */
  QTimer
  _m_timer;

  /**
   * @brief _m_isReady
   */
  bool
  _m_isReady;

};

}

#endif // SFMLCANVAS_H
