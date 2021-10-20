#include "ctFontResource.h"

namespace ct {

FontResource::FontResource()
  : data(nullptr),
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
  if(data != nullptr) {
    delete data.data();
  }

  return;
}

}

