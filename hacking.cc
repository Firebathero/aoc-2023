#include <iostream>
#include <range/v3/all.hpp>

using namespace ranges;

int main(){
    auto v = {20,10,15};
    auto r_inv = v | views::transform([](int x){return 1.0 / x;});
    auto val = 1.0 / fold_left(r_inv,0.0,std::plus{});
    std::cout << val;
}