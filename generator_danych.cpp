#include <iostream>
#include <fstream>

int main()
{
 int m;
 int n;
 int p[n];

 std::cout<<"Podaj liczbe procesorow: ";
 std::cin>>m;

 std::cout<<"Podaj liczbe procesow: ";
 std::cin>>n;

 std::ofstream plik("dane.txt");
 plik << m << std::endl;

 for(int i = 0; i < n; i++){
  std::cout << "Podaj czas "<< i << " procesu: ";
  std::cin >> p[i];
  plik << p[i] << std::endl;
 }
 
 return 0;
 
}