void inverse(int *a, int *b)
{
    int tmp = *a;
    *a = *b ;
    *b = tmp;
}
void inverse(int& a, int& b)
{
    int tmp = a ; a=b; b=tmp;
}
