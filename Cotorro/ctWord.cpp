#include "ctWord.h"

#include <QUuid>

#include "ctCotorro.h"

namespace ct {

Word::Word()
  : _m_word(""),
    _m_data(""),
    _m_start(0.0f),
    _m_end(0.0f)
{
  return;
}

void Word::init
(
    const QString &_word,
    const float &_start,
    const float &_end,
    const QString &_data
)
{
  _m_word = _word;
  _m_start = _start;
  _m_end = _end;
  _m_data = _data;

  return;
}

eOPRESULT::E
Word::init(QXmlStreamReader &_reader)
{
  // Get attributes.
  QXmlStreamAttributes attributes = _reader.attributes();

  // Check that all attributes exists in the element.
  if(!attributes.hasAttribute("word") ||
     !attributes.hasAttribute("start") ||
     !attributes.hasAttribute("end") ||
     !attributes.hasAttribute("data")
  ) {

    // Console Error.
    Cotorro::Log (
      eLOGTYPE::kError,
      QObject::tr("| Word | One or more attributes were not found in the XML.")
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
  _m_word = attributes.value(QObject::tr("word")).toString();
  _m_data = attributes.value(QObject::tr("data")).toString();
  _m_start = attributes.value(QObject::tr("start")).toFloat();
  _m_end = attributes.value(QObject::tr("end")).toFloat();

  // Reach the end of the element.
  while(!_reader.atEnd()) {
    QXmlStreamReader::TokenType token = _reader.readNext();
    if(token == QXmlStreamReader::EndElement) {
      return eOPRESULT::kOk;
    }
  }

  // Return failure if the end of the document is reached.
  return eOPRESULT::kFail;
}

eOPRESULT::E
Word::save(QXmlStreamWriter &_writer)
{
  _writer.writeStartElement(QObject::tr("Word"));

  _writer.writeAttribute(QObject::tr("word"), _m_word);
  _writer.writeAttribute(QObject::tr("start"), QString::number(_m_start));
  _writer.writeAttribute(QObject::tr("end"), QString::number(_m_end));
  _writer.writeAttribute(QObject::tr("data"), _m_data);

  _writer.writeEndElement();

  return eOPRESULT::kOk;
}

void
Word::setWord(const QString &_word)
{
  _m_word = _word;
  return;
}

QString
Word::getWord()
{
  return _m_word;
}

void
Word::setData(const QString &_data)
{
  _m_data = _data;
  return;
}

QString
Word::getData()
{
  return _m_data;
}

void
Word::setStart(const float &_start)
{
  _m_start = _start;
  return;
}

float
Word::getStart()
{
  return _m_start;
}

void
Word::setEnd(const float &_end)
{
  _m_end = _end;
  return;
}

float
Word::getEnd()
{
  return _m_end;
}

}

