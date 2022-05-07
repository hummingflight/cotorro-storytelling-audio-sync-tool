#include "ctFontResource.h"

namespace ct {

FontResource::FontResource()
  : data(),
    sfmlFont()
{
  return;
}

FontResource::~FontResource()
{
  destroy();
  return;
}

void FontResource::destroy()
{
  if(!data.isNull()) {
    data.clear();
  }

  return;
}

}

