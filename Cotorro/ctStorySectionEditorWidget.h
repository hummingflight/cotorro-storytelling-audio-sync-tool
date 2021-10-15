#ifndef STORYSECTIONEDITORWIDGET_H
#define STORYSECTIONEDITORWIDGET_H

#include "ctSfmlCanvas.h"

namespace ct {

/**
 * @brief The StorySectionEditorWidget class
 */
class StorySectionEditorWidget :
    public SfmlCanvas
{
  Q_OBJECT

public:

  /**
   * @brief Constructor
   *
   * @param _parent
   * @param _position
   * @param _size
   */
  explicit StorySectionEditorWidget
  (
    QWidget* _parent,
    const QPoint& _position,
    const QSize& _size
  );

private:

  /**
   * @brief onInit
   */
  void
  onInit() override;

  /**
   * @brief onUpdate
   */
  void
  onUpdate() override;
};

}

#endif // STORYSECTIONEDITORWIDGET_H
