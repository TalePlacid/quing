#ifndef LOCAL8BITSTRINGCONVERTER_H
#define LOCAL8BITSTRINGCONVERTER_H

#include <string>
using namespace std;

class Local8BitStringConverter{
public:
    Local8BitStringConverter();
    ~Local8BitStringConverter();

    static string Convert(string source);
};

#endif // LOCAL8BITSTRINGCONVERTER_H
