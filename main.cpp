#include "mp.hpp"
#include <type_traits>
#include <iostream>
#include <vector>

template <typename T> void PrintInfo(const std::string &var_name);

template <>
void PrintInfo<double>(const std::string &var_name)
{
   std::cout << "The vector " << var_name << " has elements of type: double\n";
}

template <>
void PrintInfo<float>(const std::string &var_name)
{
   std::cout << "The vector " << var_name << " has elements of type: float\n";
}

int main(int argc, char **argv)
{
   mp::Vector v1(10);
   mp::fp64::Vector v2(10);
   mp::fp32::Vector v3(10);

   PrintInfo<decltype(v1)::ElemType>("v1");
   PrintInfo<decltype(v2)::ElemType>("v2");
   PrintInfo<decltype(v3)::ElemType>("v3");
}
