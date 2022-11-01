#ifndef H_SortedHouseListType
#define H_SortedHouseListType
#include <iostream>
#include <string>
using namespace std;

class HouseType {

public:
  int id, rooms, bathrooms, rental_price;
  double area;
  string address_city, address_district, address_street, building_name;
  bool type;
  HouseType(int Id, double Area, int Rooms, int B_rooms, int R_price,
            string A_city, string A_dist, string A_str, string B_name = "",
            bool ty = true) {
    id = Id;
    area = Area;
    rooms = Rooms;
    bathrooms = B_rooms;
    rental_price = R_price;
    address_city = A_city;
    address_district = A_dist;
    address_street = A_str;
    building_name = B_name;
    type = ty;
  }
  HouseType() {
    id = 0;
    area = 0;
    rooms = 0;
    bathrooms = 0;
    rental_price = 0;
    address_city = "";
    address_district = "";
    address_street = "";
    building_name = "";
    type = true;
  }
  void printHouseInfo() { // o(1)
    cout << " with id: " << id << " & area: " << area
         << " and the number of rooms: " << rooms
         << " also bathrooms: " << bathrooms
         << " with the rental_price: " << rental_price
         << "JD\n address (city: " << address_city
         << " distict: " << address_district << " street: " << address_street
         << ")\n building owner: " << building_name;
    if (type)
      cout << "'s house\n";
    else
      cout << "'s Apartment\n";
    cout << "//*********************************************\n"; // to separate
                                                                 // them
  }
};
class HouseNode {
public:
  HouseType house;
  HouseNode *link;
};
class SortedHouseListType {
  HouseNode *first, *last;
  int counter;

public:
  SortedHouseListType() {
    counter = 0;
    last = first = NULL;
  }

  void destroyList() { // o(n)
    while (first != NULL) {
      HouseNode *y;
      y = first->link;
      delete first;
      first = y;
    }
    last = NULL;
    counter = 0;
  }
  /* case 1: isn't empty
     case 2: is empty */
  void print() { // o(n)
    int c = 1;
    HouseNode *Reader = first;
    if (Reader == NULL) {
      cout << "The List is Empty\n";
    } else {
      while (Reader != NULL) {
        cout << "Building NO(" << c++ << ")";
        Reader->house.printHouseInfo();
        Reader = Reader->link;
      }
    }
  }
  void insertHouse(const HouseType &newItem) { // o(n)
    // sorted from less to high rental price
    counter++;
    HouseNode *temp = new HouseNode;
    temp->house = newItem;
    temp->link = NULL;
    // empty
    if (first == NULL) {
      last = first = temp;
    }
    if (first->house.rental_price >= temp->house.rental_price) {
      temp->link = first;
      first = temp;
    } else if (last->house.rental_price <= temp->house.rental_price) {
      last->link = temp;
      last = temp;
    } else {
      HouseNode *Te = first, *o = first;
      bool problem = 1;
      while (problem && Te != NULL) {
        if (Te->house.rental_price >= temp->house.rental_price) {
          temp->link = Te;
          o->link = temp;
          problem = 0;
        }
        o = Te;
        Te = Te->link;
      }
    }
  }
  /* case 1: isn't empty
     case 2: first house has this id
     case 3: is empty
     case 4: last house has this id*/
  void RentHouse(int ID) { // o(n)
    HouseNode *temp = first, *temp1;
    while (temp->house.id != ID && temp != NULL) {
      temp1 = temp;
      temp = temp->link;
    }
    if (temp != NULL && temp != first) {
      temp1->link = temp->link;
      delete temp;
      counter--;
    } else if (temp == first && temp != NULL) {
      temp1 = temp->link;
      first = temp1;
      delete temp;
      counter--;
    } else {
      cout << "House's ID is not found\n";
    }
    cout << "the list after renting the house with the id " << ID << '\n';
    print();
  }
  void searchByRentalPrice(int renPrice) { // o(n)
    HouseNode *temp = first;
    bool problem = 1;
    if (first->house.rental_price > renPrice) {
      cout << "No Houses with the rental_price entered or less found\n";
    } else {
      while (temp->house.rental_price <= renPrice && temp != NULL) {
        temp->house.printHouseInfo();
        temp = temp->link;
      }
    }
  }
  void searchByLocation(string c, string dist) { // o(n)
    HouseNode *temp = first;
    bool problem = 1;
    while (temp != NULL) {
      // if (temp->house.address_city == c && temp->house.address_district ==
      // dist)
      if (temp->house.address_city.compare(c) == 0 &&
          (temp->house.address_district).compare(dist) == 0) {
        temp->house.printHouseInfo();
        problem = 0;
      }
      temp = temp->link;
    }
    if (problem)
      cout << "No building found on the location that you insert\n";
  }
  int CountByRoomNum(int rn) { // o(n)
    HouseNode *temp = first;
    int cc = 0;
    while (temp != NULL) {
      if (temp->house.rooms == rn)
        cc++;
      temp = temp->link;
    }
    return cc;
  }
  int CountByType(bool t) { // o(n)
    HouseNode *temp = first;
    int cc = 0;
    while (temp != NULL) {
      if (temp->house.type == t)
        cc++;
      temp = temp->link;
    }
    return cc;
  }
  void updatePrice(int ID, int newPrice) { // o(n^2) because of the insert after delete
    cout << "updating the price of the house with the id " << ID << " to JD"
         << newPrice << '\n';
    HouseNode *temp = first, *o = first;
    HouseType tt;
    bool problem = 1;
    if (first->house.id == ID) {
      tt = first->house;
      first = first->link;
      delete o;
      problem = 0;
    }
    while (temp != NULL && problem) {
      if (temp->house.id == ID) {
        problem = 0;
        tt = temp->house;
        if (temp->link == NULL) {
          last = o;
          o->link = NULL;
        } else
          o->link = temp->link;
        delete temp;
      } else {
        o = temp;
        temp = temp->link;
      }
    }
    if (!problem) {
      tt.rental_price = newPrice;
      cout << "the list after updating the price\n";
      insertHouse(tt);
      print();
    } else
      cout << "The ID you insert is not exist\n";
  }
  ~SortedHouseListType() { destroyList(); }
};

#endif