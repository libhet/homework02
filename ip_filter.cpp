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

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

using ip_tuple = std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>;
using ip_type = std::vector<std::string>;
using ip_container = std::vector<ip_type>;

namespace std {
    std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& vs)
    {
        return os << vs.at(0) << "." << vs.at(1) << "." << vs.at(2) << "." << vs.at(3) << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    try
    {
        ip_container ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        // TODO reverse lexicographically sort

        std::sort(std::begin(ip_pool),std::end(ip_pool),
                  [](const std::vector<std::string> &a, const std::vector<std::string> &b)
                  {
                      uint32_t ip_a = 0, ip_b = 0;
                      for(int i = 0; i < 4; ++i) {
                          ip_a |= (unsigned char)std::stoi(a[i]) << (24 - (i*8));
                          ip_b |= (unsigned char)std::stoi(b[i]) << (24 - (i*8));
                      }
                      return ip_a > ip_b;
                  });

        for(auto &ip: ip_pool) {
            std::cout << ip;
        }

        // TODO filter by first byte and output

        auto filter = [&](unsigned char byte){
            std::copy_if(std::begin(ip_pool),std::end(ip_pool),
                         std::ostream_iterator<decltype(*std::begin(ip_pool))>(std::cout),
                         [byte](const ip_type & ip) {
                             auto first_byte = (unsigned char)stoi(ip.at(0));
                             return (first_byte == byte);
                         }
            );
        };
        filter(1);

        // TODO filter by first and second bytes and output

        auto filter2 = [&](unsigned char byte_1, unsigned char byte_2){
            std::copy_if(std::begin(ip_pool),std::end(ip_pool),
                         std::ostream_iterator<decltype(*std::begin(ip_pool))>(std::cout),
                         [byte_1,byte_2](const ip_type & ip) {
                             auto first_byte   = (unsigned char)stoi(ip.at(0));
                             auto second_byte  = (unsigned char)stoi(ip.at(1));
                             return (first_byte == byte_1 && second_byte == byte_2);
                         }
            );
        };
        filter2(46,70);
        // ip = filter(46, 70)

        // TODO filter by any byte and output
        // ip = filter_any(46)
        auto filter_any = [&](unsigned char any_byte){
            std::copy_if(std::begin(ip_pool),std::end(ip_pool),
                         std::ostream_iterator<decltype(*std::begin(ip_pool))>(std::cout),
                         [any_byte](const ip_type & ip) {
                             return std::any_of(ip.begin(),ip.end(),
                                                [any_byte](std::string s){
                                                    return stoi(s) == any_byte;
                                                }
                             );
                         }
            );
        };
        filter_any(46);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}