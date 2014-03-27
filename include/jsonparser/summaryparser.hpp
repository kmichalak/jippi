#ifndef SUMMARYPARSER_H
#define SUMMARYPARSER_H

#include "fieldparser.hpp"

namespace jippi {

class SummaryFieldParser : public FieldParser
{
public:
    SummaryFieldParser();
    virtual ~SummaryFieldParser();
    virtual field * parse(Json::Value &fieldJsonDocument);
};

}

#endif // SUMMARYPARSER_H
