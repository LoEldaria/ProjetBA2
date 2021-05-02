#pragma once

#include <iostream>
#include "SupportADessin.h"

class Montagne;
class Ciel;
class Systeme;

class TextViewer : public SupportADessin {
public:
    TextViewer (std::ostream& f) : flot(f) {}
    
    virtual ~TextViewer() = default;
    TextViewer(TextViewer const&)           = delete;
    TextViewer& operator=(TextViewer const&) = delete;
    TextViewer(TextViewer&&)            = default;
    TextViewer& operator=(TextViewer&&) = default;

    virtual void dessine(Montagne const& a_dessiner) override;
    virtual void dessine(Ciel const& a_dessiner) override;
    virtual void dessine(Systeme const& a_dessiner) override;
    
private:
    std::ostream& flot;
};