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
            double p_inf;
            double temp_inf;
            double h_inf;
            double cte_Bernoulli;

            Parametres(double v, double p, double t):v_inf(v),p_inf(p),temp_inf(t)
            {
                h_inf=((7.0/2.0)*(R/mmolaire_airsec)*temp_inf);
                cte_Bernoulli=(0.5*(temp_inf*temp_inf) + h_inf);
            }
    };

}


#endif // CONSTANTES