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
using ip_container = std::vector<ip_type>;
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

//template<typename... Args>
//void filter(Args... args, int index = 0, std::ostream &os = std::cout) {
//    index = sizeof...(args);
//
//}

void print_ip(ip_type &ip) {
    std::cout << (int)ip.at(0) << "." <<
                 (int)ip.at(1) << "." <<
                 (int)ip.at(2) << "." <<
                 (int)ip.at(3) << "\n" ;
}
void print_ip_vector(ip_container &ipc) {
    for(auto & it : ipc) {
        print_ip(it);
    }
}

ip_container filter(uint8_t first, const ip_container& ip_pool) {
    ip_container r;
    r.reserve(ip_pool.size());
    std::copy_if(std::begin(ip_pool),std::end(ip_pool),std::back_inserter(r),
                 [&](const ip_type & ip){return first ==ip.at(0);});
    return r;
}
ip_container filter(uint8_t first, uint8_t second, const ip_container& ip_pool) {
    ip_container r;
    r.reserve(ip_pool.size());
    std::copy_if(std::begin(ip_pool),std::end(ip_pool),std::back_inserter(r),
                 [&](const ip_type & ip){return first ==ip.at(0) && second == ip.at(1);});
    return r;
}
ip_container filter_any(uint8_t any, const ip_container& ip_pool) {
    ip_container r;
    r.reserve(ip_pool.size());
    std::copy_if(std::begin(ip_pool),std::end(ip_pool),
                 std::back_inserter(r),
                 [&](const ip_type & ip) {
                     return std::any_of(std::begin(ip),std::end(ip),
                                        [&](uint8_t byte){return byte == any;});
                 }
    );
    return r;
}



int main(int argc, char const *argv[])
{
    try
    {
        std::ifstream in("in.txt");
        std::cin.rdbuf(in.rdbuf());

        std::ofstream out("out2.txt");
        std::cout.rdbuf(out.rdbuf());

        ip_vector ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            auto v = split<ve_str>(line, '\t');
            ip_pool.emplace_back(split(v.at(0), '.'));
        }


        // TODO reverse lexicographically sort
        std::sort(std::begin(ip_pool),std::end(ip_pool), std::greater<decltype(*std::begin(ip_pool))>());

        for(auto &ip: ip_pool) {
            print_ip(ip);
        }

//        auto start  =  std::chrono::steady_clock::now();
//                        auto filter = [&](unsigned char first){
//                                        ip_vector r;
//                                        r.reserve(ip_pool.size());
//                                        std::copy_if(std::begin(ip_pool),std::end(ip_pool), std::back_inserter(r),
//                                                     [first](const ip_type & ip){return first == ip[0];}
//                                        );
//                            return r;
//                        };
//        auto ip = filter(1);
//                        print_ip_vector(ip);
//        auto end   =  std::chrono::steady_clock::now();
//        auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
//        std::cout << "vector: "  << elapsed.count() << std::endl;


        // TODO filter by first byte and output
        auto ip = filter(1,ip_pool);
        print_ip_vector(ip);

        // TODO filter by first and second bytes and output
        auto ip2 = filter(46,70,ip_pool);
        print_ip_vector(ip2);

        // TODO filter by any byte and output
        auto ip3 = filter_any(46,ip_pool);
        print_ip_vector(ip3);

        out.close();
        system("out2.txt");

    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }


    return 0;
}