#include <iostream>
#include <fstream>

int main()
{
 int m = 5;
 int n = 9;
 int p[n];
 std::ofstream plik("dane.txt");
 plik << m << std::endl;

 for(int i = 0; i < n; i++){
  std::cout << "Podaj czas "<< i << " procesu: ";
  std::cin >> p[i];
  plik << p[i] << std::endl;
 }
 
 return 0;
 
}