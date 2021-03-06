#include "ctStorySectionEditorWidget.h"

#include <QMouseEvent>

#include "ctCotorro.h"

namespace ct {

float StorySectionEditorWidget::_MIN_PIXEL_PER_SECOND = 10.0f;
float StorySectionEditorWidget::_MAX_PIXEL_PER_SECOND = 300.0f;
float StorySectionEditorWidget::_PADDING_TOP = 10.0f;
float StorySectionEditorWidget::_PADDING_BOTTOM = 10.0f;
float StorySectionEditorWidget::_PADDING_RIGHT = 10.0f;
float StorySectionEditorWidget::_PADDING_LEFT = 10.0f;
float StorySectionEditorWidget::_PADDING_BETWEEN = 5.0f;

StorySectionEditorWidget::StorySectionEditorWidget
(
  QWidget* _parent,
  const QPoint& _position,
  const QSize& _size
) :
  SfmlCanvas(_parent, _position, _size),
  _m_clearColor(200, 200, 200),
  _m_view(sf::Vector2f(0,0), sf::Vector2f(300.0f,200.0f)),
  _m_waveFormEditor(this),
  _m_wordsEditor(this),
  _m_waveFormEditorSlider(this),
  _m_pActiveStorySection(nullptr),
  _m_pActiveWord(nullptr),
  _m_pixelsPerSecond(0),
  _m_zoom(0),
  _m_viewportTimePosition(0.0f)
{
  return;
}

void
StorySectionEditorWidget::setZoom(const float &_zoom)
{
  _m_zoom = _zoom;
  _m_pixelsPerSecond = StorySectionEditorWidget::_MIN_PIXEL_PER_SECOND
                     + (StorySectionEditorWidget::_MAX_PIXEL_PER_SECOND - StorySectionEditorWidget::_MIN_PIXEL_PER_SECOND)
                     * _m_zoom;

  moveViewport(0.0f);
  return;
}

void
StorySectionEditorWidget::resizeEvent(QResizeEvent *_event)
{
  // Resize SFML Window.
  sf::RenderWindow::setSize(sf::Vector2u(width(), height()));

  // Resize SFML View.
  resetView();

  // Update frames
  updateFramesTransformations();

  // Update viewport
  moveViewport(0.0f);
  return;
}

void
StorySectionEditorWidget::updateFrames()
{
  _m_waveFormEditor.onUpdate(*this);
  _m_wordsEditor.onUpdate(*this);
  _m_waveFormEditorSlider.onUpdate(*this);
  return;
}

void
StorySectionEditorWidget::updateFramesTransformations()
{
  quint32 w = width();
  quint32 h = height();

  sf::Vector2u position(0, 0);
  quint32 frameH = h * 0.85f;

  _m_waveFormEditor.setPosition(position.x, position.y);
  _m_waveFormEditor.setSize(w, frameH);

  position.y += frameH;
  frameH = h * 0.10f;

  _m_wordsEditor.setPosition(position.x, position.y);
  _m_wordsEditor.setSize(w, frameH);

  position.y += frameH;
  frameH = h * 0.05f;

  _m_waveFormEditorSlider.setPosition(position.x, position.y);
  _m_waveFormEditorSlider.setSize(w, frameH);

  return;
}

StorySection*
StorySectionEditorWidget::getActiveStorySection()
{
  return _m_pActiveStorySection;
}

Word* 
StorySectionEditorWidget::getActiveWord()
{
  return _m_pActiveWord;
}

float
StorySectionEditorWidget::getViewportPosition()
{
  return _m_viewportTimePosition;
}

float
StorySectionEditorWidget::getViewportNormalizedPosition()
{
  float mediaLength = getMediaLength();
  if(mediaLength <= 0.0f) {
    return 0.0f;
  }

  return getViewportPosition() / mediaLength;
}

float
StorySectionEditorWidget::getViewportLength()
{
  if(_m_pixelsPerSecond == 0.0f) {
    return 0.0f;
  }

  return (width() - StorySectionEditorWidget::_PADDING_RIGHT - StorySectionEditorWidget::_PADDING_LEFT) / _m_pixelsPerSecond;
}

float
StorySectionEditorWidget::getViewportNormalizedLength()
{
  float mediaLength = getMediaLength();
  if(mediaLength <= 0.0f) {
    return 0.0f;
  }

  return  getViewportLength() / mediaLength;
}

float
StorySectionEditorWidget::getMediaLength()
{
  AudioManager& audioManager = Cotorro::Instance()->getAudioManager();
  return audioManager.getDuration();
}

float 
StorySectionEditorWidget::getCursorPosition()
{
  return _m_waveFormEditor.getCursorPosition();
}

void
StorySectionEditorWidget::onActiveSectionChanged(StorySection *_pStorySection)
{
  _m_pActiveStorySection = _pStorySection;
  setViewportPosition(0.0f);

  _m_waveFormEditor.onStorySectionChanged(_pStorySection);
  _m_waveFormEditorSlider.onStorySectionChanged(_pStorySection);
  return;
}


void 
StorySectionEditorWidget::onActiveWordChanged(ct::Word* _pWord)
{
  _m_pActiveWord = _pWord;

  _m_waveFormEditor.onActiveWordChanged(_pWord);
  _m_wordsEditor.onActiveWordChanged(_pWord);
  return;
}

void
StorySectionEditorWidget::mousePressEvent(QMouseEvent *e)
{
  _m_waveFormEditor.onMousePressed(e);
  _m_waveFormEditorSlider.onMousePressed(e);
  return;
}

void
StorySectionEditorWidget::mouseMoveEvent(QMouseEvent *e)
{
  _m_waveFormEditor.onMouseMoved(e);
  _m_waveFormEditorSlider.onMouseMoved(e);
  return;
}

void
StorySectionEditorWidget::mouseReleaseEvent(QMouseEvent *e)
{
  _m_waveFormEditor.onMouseReleased(e);
  _m_waveFormEditorSlider.onMouseReleased(e);
  return;
}

void
StorySectionEditorWidget::mouseDoubleClickEvent(QMouseEvent *e)
{
  _m_waveFormEditor.onMouseDoubleClicked(e);
  _m_waveFormEditorSlider.onMouseDoubleClicked(e);
  return;
}

float
StorySectionEditorWidget::getPixelsPerSecond()
{
  return _m_pixelsPerSecond;
}

const void
StorySectionEditorWidget::setViewportPosition(const float &_time)
{
  updateViewportPosition(_time);

  _m_waveFormEditorSlider.onViewportMoved(_m_viewportTimePosition);
  _m_waveFormEditor.onViewportMoved(_m_viewportTimePosition);
  _m_wordsEditor.onViewportMoved(_m_viewportTimePosition);
  return;
}

void
StorySectionEditorWidget::moveViewport(const float &_seconds)
{
  float viewportWidth = getViewportLength();
  float trackDuration = getMediaLength();
  if(viewportWidth >= trackDuration) {
    _m_viewportTimePosition = 0.0f;
  }
  else {
    float viewportFinalPointPosition = _seconds
                                     + _m_viewportTimePosition
                                     + viewportWidth;

    if(viewportFinalPointPosition > trackDuration){
      _m_viewportTimePosition += _seconds
                              + trackDuration
                              - viewportFinalPointPosition;
    }
    else {
      _m_viewportTimePosition += _seconds;
    }

    if(_m_viewportTimePosition < 0.0f) {
      _m_viewportTimePosition = 0.0f;
    }
  }

  _m_waveFormEditorSlider.onViewportMoved(_m_viewportTimePosition);
  _m_waveFormEditor.onViewportMoved(_m_viewportTimePosition);
  _m_wordsEditor.onViewportMoved(_m_viewportTimePosition);
  return;
}

const float&
StorySectionEditorWidget::getZoom()
{
  return _m_zoom;
}

void
StorySectionEditorWidget::onInit()
{
  _m_elapsed = 0.0f;
  setZoom(0.0f);

  // Set SFML View
  resetView();

  // Init Frames.
  _m_waveFormEditor.init();
  _m_waveFormEditor.setStorySectionEditorWidget(this);
  _m_waveFormEditor.setMargin(
    StorySectionEditorWidget::_PADDING_LEFT,
    StorySectionEditorWidget::_PADDING_TOP,
    StorySectionEditorWidget::_PADDING_RIGHT,
    StorySectionEditorWidget::_PADDING_BETWEEN
  );
  _m_waveFormEditor.updateTimeline();

  _m_wordsEditor.init();
  _m_wordsEditor.setMinimumSize(10, 20);
  _m_wordsEditor.setMargin(
    StorySectionEditorWidget::_PADDING_LEFT,
    StorySectionEditorWidget::_PADDING_BETWEEN,
    StorySectionEditorWidget::_PADDING_RIGHT,
    StorySectionEditorWidget::_PADDING_BETWEEN
  );

  _m_waveFormEditorSlider.init();  
  _m_waveFormEditorSlider.setMinimumSize(10, 20);
  _m_waveFormEditorSlider.setMargin(
    StorySectionEditorWidget::_PADDING_LEFT,
    StorySectionEditorWidget::_PADDING_BETWEEN,
    StorySectionEditorWidget::_PADDING_RIGHT,
    StorySectionEditorWidget::_PADDING_BOTTOM
  );

  // Widget properties.
  QWidget::setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  // Connections
  Project& project = Cotorro::Instance()->getProject();
  StorySectionManager& storySectionManager = project.getStorySectionManager();

  connect(&storySectionManager, &StorySectionManager::activeSectionChanged, this, &StorySectionEditorWidget::onActiveSectionChanged);
  connect(&storySectionManager, &StorySectionManager::activeWordChanged, this, &StorySectionEditorWidget::onActiveWordChanged);

  return;
}

void
StorySectionEditorWidget::onUpdate()
{
  // Delta time.
  _m_elapsed += getDeltaTime().asSeconds();

  // Clear canvas.
  sf::RenderWindow::clear(_m_clearColor);

  // Update Frames.
  updateFrames();

  return;
}

void
StorySectionEditorWidget::resetView()
{
  quint32 w = width();
  quint32 h = height();

  _m_view.setSize(w, h);
  _m_view.setCenter(w * 0.5, h * 0.5);
  sf::RenderWindow::setView(_m_view);

  return;
}

void
StorySectionEditorWidget::updateViewportPosition(const float &_time)
{
  float viewportWidth = getViewportLength();
  float trackDuration = getMediaLength();
  if(viewportWidth >= trackDuration) {
    _m_viewportTimePosition = 0.0f;
  }
  else {
    float viewportFinalPointPosition = _time
                                     + viewportWidth;

    if(viewportFinalPointPosition > trackDuration){
      _m_viewportTimePosition = _time
                              + trackDuration
                              - viewportFinalPointPosition;
    }
    else {
      _m_viewportTimePosition = _time;
    }

    if(_m_viewportTimePosition < 0.0f) {
      _m_viewportTimePosition = 0.0f;
    }
  }
}

}

