//
// Created by siddharth on 04/04/2021.
//

#ifndef PROJET_SUPPORTADESSIN_H
#define PROJET_SUPPORTADESSIN_H

class Montagne;
class Ciel;
class Systeme;

class SupportADessin
        {
                public:
                virtual ~SupportADessin() = default;
    SupportADessin(SupportADessin const&)            = delete;
    SupportADessin& operator=(SupportADessin const&) = delete;
    SupportADessin(SupportADessin&&)            = default;
    SupportADessin& operator=(SupportADessin&&) = default;
    SupportADessin() = default;

                virtual void dessine(Montagne const&) = 0;
                virtual void dessine(Ciel const&) = 0;
                virtual void dessine(Systeme const&) = 0;

        };



#endif //PROJET_SUPPORTADESSIN_H
