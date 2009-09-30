template<int ilosc_wymiarow>struct tablica{
    tablica<ilosc_wymiarow-1> elementy[100];
};
int main(){
	tablica<3> dupa;
}
