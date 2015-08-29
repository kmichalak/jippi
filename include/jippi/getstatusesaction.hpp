//
// Created by kamil on 29.08.15.
//

#ifndef JIPPI_GETSTATUSESACTION_HPP
#define JIPPI_GETSTATUSESACTION_HPP

#include "jippi.hpp"
#include "jippi/action.hpp"

namespace jippi {

class GetStatusesAction : public Action
{
public:
    GetStatusesAction();
    ~GetStatusesAction();
    void perform();
};

}

#endif //JIPPI_GETSTATUSESACTION_HPP
