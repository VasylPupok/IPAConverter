#ifndef CONVERTER_H
#define CONVERTER_H

#include <string>

namespace Translate {

    using StringType = std::wstring;

    StringType toInternational(const StringType& ukranianPhonetic);

    StringType toUkranian(const StringType& ifa);

};

#endif // CONVERTER_H
