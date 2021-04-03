#ifndef CONSTANTES_H
#define CONSTANTES_H

namespace Physique {
    extern const double Pref;
    extern const double R;
    extern const double mmolaire_eau;
    extern const double mmolaire_airsec;
    extern const double g;

    class Parametres{
        public:
            double v_inf;
            double temp_inf;
            double p_inf;
            double h_inf;
            double cte_Bernoulli;

            Parametres(double v, double t, double p):v_inf(v),temp_inf(t),p_inf(p)
            {
                h_inf=((7.0/2.0)*(R/mmolaire_airsec)*temp_inf);
                cte_Bernoulli=(0.5*(v_inf*v_inf) + h_inf);
            }
    };
}


#endif // CONSTANTES