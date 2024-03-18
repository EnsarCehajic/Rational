#include "Rational.hpp"
#include <iostream>
#include <fstream>
int main(int argc, char* argv[]) {
  std::string temp;
  std::ifstream file ("input.txt");

  if(file.is_open()){
    while(std::getline(file,temp)){
      Rational temp2;
      try{
        temp2=temp;
        std::cout<<temp2<<std::endl;
      }
    	catch (const std::exception& e) {
               
                std::cout << "Greska prilikom obrade linije" << "': " << e.what() << std::endl;
            }
    }
    file.close();
  }
  else {
    std::cout<<"File nikad nije otvoren!"<<std::endl;
  }
  return 0;
}
