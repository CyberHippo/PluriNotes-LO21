#ifndef RAZ_H_INCLUDED
#define RAZ_H_INCLUDED

struct essai {
    int n;
    float x;
    void raz();
};
void raz(essai* e);
void raz(essai& e);

#endif // RAZ_H_INCLUDED
