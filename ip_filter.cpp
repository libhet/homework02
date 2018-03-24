#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
// = = = = = = = = = =
#include <fstream>
#include <algorithm>
#include <iterator>
#include <list>
#include <tuple>
#include <functional>

#include <chrono>

//using doubleDiff =  std::chrono::duration<double>;
//using msDiff =  std::chrono::duration<double>;
//auto start  =  std::chrono::steady_clock::now();
//auto end   =  std::chrono::steady_clock::now();
//time_diff diff = end - start;
//auto elapsed = duration_cast<milliseconds>(end - start);

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]

template <typename T>
T split(std::string const &str, char d) {

    T r;

    size_t start = 0;
    size_t stop = str.find_first_of(d);
        while(stop != std::string::npos)
    {
        r.emplace_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.emplace_back(str.substr(start));

    return r;
}

using ve_str = std::vector<std::string>;
using li_str = std::list<std::string>;

using ip_type = std::array<uint8_t, 4>;
using ip_vector = std::vector<ip_type>;
using ip_list = std::list<ip_type>;


ip_type split(std::string const &str, char d) {

    ip_type r = {0,0,0,0};

    size_t start = 0;
    size_t stop = str.find_first_of(d);
    int i = 0;
    while(stop != std::string::npos)
    {
        r[i] = (uint8_t)stoi(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
        i++;
    }

    r[3] = (uint8_t)stoi(str.substr(start));

    return r;
}

template<typename... Args>
void filter(Args... args) {

}

int main(int argc, char const *argv[])
{
    try
    {
        std::ifstream in("in.txt");
        std::cin.rdbuf(in.rdbuf());

        ip_list ip_pool_list;
        ip_vector ip_pool_vect;

        for(std::string line; std::getline(std::cin, line);)
        {
            auto v = split<ve_str>(line, '\t');
            ip_pool_list.emplace_back(split(v.at(0), '.'));
        }


        //reverse lexicographically sort
        auto start  =  std::chrono::steady_clock::now();
        std::sort(std::begin(ip_pool_vect),std::end(ip_pool_vect));
        auto end   =  std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        std::cout << "vector: "  << elapsed.count() << std::endl;
//        for(auto &ip: ip_pool_list) {
//            std::cout << ip;
//        }



//
//        // TODO filter by first byte and output
//
//        auto filter = [&](unsigned char byte){
//            std::copy_if(std::begin(ip_pool),std::end(ip_pool),
//                         std::ostream_iterator<decltype(*std::begin(ip_pool))>(std::cout),
//                         [byte](const ip_type & ip) {
//                             auto first_byte = (unsigned char)stoi(ip.at(0));
//                             return (first_byte == byte);
//                         }
//            );
//        };
//        filter(1);
//
//        // TODO filter by first and second bytes and output
//
//        auto filter2 = [&](unsigned char byte_1, unsigned char byte_2){
//            std::copy_if(std::begin(ip_pool),std::end(ip_pool),
//                         std::ostream_iterator<decltype(*std::begin(ip_pool))>(std::cout),
//                         [byte_1,byte_2](const ip_type & ip) {
//                             auto first_byte   = (unsigned char)stoi(ip.at(0));
//                             auto second_byte  = (unsigned char)stoi(ip.at(1));
//                             return (first_byte == byte_1 && second_byte == byte_2);
//                         }
//            );
//        };
//        filter2(46,70);
//        // ip = filter(46, 70)
//
//        // TODO filter by any byte and output
//        // ip = filter_any(46)
//        auto filter_any = [&](unsigned char any_byte){
//            std::copy_if(std::begin(ip_pool),std::end(ip_pool),
//                         std::ostream_iterator<decltype(*std::begin(ip_pool))>(std::cout),
//                         [any_byte](const ip_type & ip) {
//                             return std::any_of(ip.begin(),ip.end(),
//                                                [any_byte](std::string s){
//                                                    return stoi(s) == any_byte;
//                                                }
//                             );
//                         }
//            );
//        };
//        filter_any(46);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}