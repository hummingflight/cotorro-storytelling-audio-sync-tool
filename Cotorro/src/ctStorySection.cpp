#include "ctStorySection.h"

#include <QUuid>
#include <QRegularExpression>

#include "ctCotorro.h"

namespace ct {

StorySection::StorySection(QObject *parent) :
  QObject(parent),
  _m_name(""),
  _m_uuid(""),
  _m_audioKey(""),
  _m_content(""),
  _m_aWords()
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

eOPRESULT::E
StorySection::init(QXmlStreamReader &_reader)
{
  clearWords();

  // Get attributes.
  QXmlStreamAttributes attributes = _reader.attributes();

  // Check that all attributes exists in the element.
  if(!attributes.hasAttribute("uuid") ||
     !attributes.hasAttribute("name") ||
     !attributes.hasAttribute("audioKey") ||
     !attributes.hasAttribute("content")
  ) {

    // Console Error.
    Cotorro::Log (
      eLOGTYPE::kError,
      tr("| StorySection | One or more attributes were not found in the XML.")
    );

    // Reach the end of the element.
    while(!_reader.atEnd()) {
      QXmlStreamReader::TokenType token = _reader.readNext();
      if(token == QXmlStreamReader::EndElement) {
        return eOPRESULT::kIncompatibleObject;
      }
    }

    // Return failure if the end of the document is reached.
    return eOPRESULT::kFail;
  }

  // Fill values.
  _m_uuid = attributes.value(tr("uuid")).toString();
  _m_name = attributes.value(tr("name")).toString();
  _m_audioKey = attributes.value(tr("audioKey")).toString();
  _m_content = attributes.value(tr("content")).toString();

  // Create words and/or reach the end of the element.
  qint32 index = 0;
  while(!_reader.atEnd()) {
    QXmlStreamReader::TokenType token = _reader.readNext();
    if(token == QXmlStreamReader::StartElement) {
      if(_reader.name().toLatin1() == "Word") {

        // Create a new word.
        Word* pNewWord = new Word();

        if(pNewWord->init(_reader, index) != eOPRESULT::kOk) {
          // Something went wrong.
          delete pNewWord;
          return eOPRESULT::kFail;
        }

        // Add new word.
        _m_aWords.push_back(pNewWord);
        index++;
      }
    } else if(token == QXmlStreamReader::EndElement) {
      return eOPRESULT::kOk;
    }
  }

  // Return failure if the end of the document is reached.
  return eOPRESULT::kFail;
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

eOPRESULT::E
StorySection::save(QXmlStreamWriter &_writer)
{
  _writer.writeStartElement(tr("StorySection"));

  _writer.writeAttribute(tr("uuid"), _m_uuid);
  _writer.writeAttribute(tr("name"), _m_name);
  _writer.writeAttribute(tr("audioKey"), _m_audioKey);
  _writer.writeAttribute(tr("content"), _m_content);
  _writer.writeAttribute(tr("size"), QString::number(_m_aWords.size()));

  foreach( Word* word , _m_aWords) {
    word->save(_writer);
  }

  _writer.writeEndElement();

  return eOPRESULT::kOk;
}

void
StorySection::clearWords()
{
  qDeleteAll(_m_aWords);
  _m_aWords.clear();
}

void
StorySection::resetWords()
{
  clearWords();

  qint32 index = 0;
  float stepsSeconds = 1.0f;
  float start = 0.0f;

  QStringList words = _m_content.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
  QStringListIterator it(words);
  while(it.hasNext()) {
    Word* pWord = new Word();
    pWord->init(
      it.next(),
      start,
      start + stepsSeconds,
      "",
      index
    );
    _m_aWords.push_back(pWord);
    start += stepsSeconds;
    index++;
  }
  return;
}

const QList<Word *>&
StorySection::getWordsList()
{
  return _m_aWords;
}

void
StorySection::destroy()
{
  clearWords();
  return;
}
}
