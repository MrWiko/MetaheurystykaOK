#include <iostream>
#include <fstream>
#include <vector>

int main()
{
 int m;
 int n;
 std::vector<int> p;

 std::cout<<"Podaj liczbe procesorow: ";
 std::cin>>m;

 std::cout<<"Podaj liczbe procesow: ";
 std::cin>>n;

 p.resize(n);

 std::ofstream plik("dane1.txt");
 plik << m << std::endl;

 for(int i = 0; i < n; i++){
  std::cout << "Podaj czas "<< i << " procesu: ";
  std::cin >> p[i];
  plik << p[i] << std::endl;
 }
 plik.close();

 return 0;
}
