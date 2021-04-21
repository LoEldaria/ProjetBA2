//
// Created by siddharth on 04/04/2021.
//

#pragma once

#include "SupportADessin.h"

class Dessinable {

protected :
    SupportADessin* blank_paper ;

public :
    virtual ~Dessinable() = default;

    Dessinable(Dessinable const&)            = default;
    Dessinable& operator=(Dessinable const&) = default;
    Dessinable(Dessinable&&)                 = default;
    Dessinable& operator=(Dessinable&&)      = default;
    Dessinable() = default;

    Dessinable(SupportADessin* support): blank_paper(support){}
    virtual void dessine_sur(SupportADessin& support) = 0 ;
};




