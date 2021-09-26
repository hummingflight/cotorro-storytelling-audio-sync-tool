#include "ctStorySection.h"

#include <QUuid>

namespace ct {

StorySection::StorySection(QObject *parent) :
  QObject(parent),
  _m_name(""),
  _m_uuid(""),
  _m_audioKey(""),
  _m_content("")
{
  return;
}

void
StorySection::init()
{
  _m_uuid = QUuid::createUuid().toString(QUuid::StringFormat::Id128);
  return;
}

void
StorySection::init(const QString &_name)
{
  init();
  _m_name = _name;
  return;
}

QString
StorySection::getName()
{
  return _m_name;
}

void
StorySection::setName(const QString &_name)
{
  _m_name = _name;
  return;
}

QString
StorySection::getUuid()
{
  return _m_uuid;
}

QString
StorySection::getAudioKey()
{
  return _m_audioKey;
}

void
StorySection::setAudioKey(const QString &_audioKey)
{
  _m_audioKey = _audioKey;
  return;
}

QString
StorySection::getContent()
{
  return _m_content;
}

void
StorySection::setContent(const QString &_content)
{
  _m_content = _content;
  return;
}

}
