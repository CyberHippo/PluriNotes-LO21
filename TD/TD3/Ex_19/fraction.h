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
    fraction (int n, int d); // on d�clare les constructeurs
    fraction (int n);
    fraction ();
    inline int getNumerateur() const; // l'objet qui fait appel � cette fonction ne peut pas �tre modifi�
    inline int getDenominateur() const;
    fraction somme(const fraction &F1) const; // on la d�clare comme m�thode de la classe
    void setFraction (int n, int d);

};
// on d�finit les m�thodes en dehors de la classe sinon �a bugue
inline int fraction::getNumerateur() const
{
    return m_numerateur;
}
inline int fraction::getDenominateur () const
{
    return m_denominateur;
}
fraction somme (const fraction &f1, const fraction &f2); // on la d�clare comme fonction

}
