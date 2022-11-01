#include "SortedHouseListType.h"
#include <iostream>
#include <string>
using namespace std;
int main(void) {
  SortedHouseListType sor;
  int x, y, z, u, n;
  double t;
  string s, ss, sss, ssss;
  bool r;
  cout << "enter the number of cases you want to try\n";
  cin >> n;
  while (n--) {
    cout << "please enter the house information\n";
    cin >> x >> t >> y >> z >> u >> s >> ss >> sss >> ssss >> r;
    HouseType h(x, t, y, z, u, s, ss, sss, ssss, r);
    sor.insertHouse(h);
  }
  sor.print();
  cout << "enter the id that you want to change the price of it \n";
  cin >> x >> y;
  sor.updatePrice(x, y);
  cout << "Enter the number of rooms you want\n";
  cin >> x;
  cout << "the number of building that have "<<x<<" Number of rooms is: "<<sor.CountByRoomNum(x)<<'\n';
  cout <<"enter the address city and ditrict to print it's building details\n";
  cin >> s >> ss;
  sor.searchByLocation(s,ss);
  cout << "Enter the id of the house you are planning to rent\n";
  cin >> x;
  sor.RentHouse(x);
  cout << "Enter the price that you can buy with it\n";
  cin >> x;
  sor.searchByRentalPrice(x);



}
