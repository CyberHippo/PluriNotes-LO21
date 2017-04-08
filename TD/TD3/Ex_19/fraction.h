namespace MATH
{

class fraction
{
private:
    int m_numerateur;
    int m_denominateur;
    void simplification();
public:
    ~fraction()
    {

    }
    fraction (int n, int d); // on déclare les constructeurs
    fraction (int n);
    fraction ();
    inline int getNumerateur() const; // l'objet qui fait appel à cette fonction ne peut pas être modifié
    inline int getDenominateur() const;
    fraction somme(const fraction &F1) const; // on la déclare comme méthode de la classe
    void setFraction (int n, int d);

};
// on définit les méthodes en dehors de la classe sinon ça bugue
inline int fraction::getNumerateur() const
{
    return m_numerateur;
}
inline int fraction::getDenominateur () const
{
    return m_denominateur;
}
fraction somme (const fraction &f1, const fraction &f2); // on la déclare comme fonction

}
