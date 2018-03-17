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

namespace CHECK
{
    struct No {};
    template<typename... Args>
    No emplace_back(Args&& ...args);

    template<typename T, typename Arg = T>
    struct EmplaceBackExists
    {
        enum { value = !std::is_same<decltype(*(T*)(0) == *(Arg*)(0)), No>::value };
    };
}

template<typename ValueType, template<typename T = ValueType> class ContainerType>
ContainerType<ValueType> split(const std::string &str, char d) {
    ContainerType<ValueType> r;
    static_assert(CHECK::EmplaceBackExists<ContainerType<ValueType>>::value, "Container doesn't have emplace_back()");

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.emplace_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.emplace_back(str.substr(start));

    return r;
};

template<typename ValueType>
std::tuple<ValueType> split<ValueType, std::tuple<ValueType>>(const std::string &str, char d) {
    std::tuple<std::common_type<ValueType>> r;
    //Создать приведение всех типов к одному внутри тапла. Использовать размер ValueTypes
    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r = std::tuple_cat(r, std::tuple<ValueType>(stoi(str.substr(start, stop - start)))); //Работает только с числами? INT
    start = stop + 1;
    stop = str.find_first_of(d, start);
    }

    r = std::tuple_cat(r, std::tuple<ValueType>(stoi(str.substr(start, stop - start))));

    return r;
};


template<typename ValueType, typename... ValueTypes>
std::tuple<ValueTypes...> split(const std::string &str, char d) {
    std::tuple<std::common_type<ValueType>> r;
//Создать приведение всех типов к одному внутри тапла. Использовать размер ValueTypes
    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r = std::tuple_cat(r, std::tuple<ValueType>(stoi(str.substr(start, stop - start)))); //Работает только с числами? INT
        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r = std::tuple_cat(r, std::tuple<ValueType>(stoi(str.substr(start, stop - start))));

    return r;
}

std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> make_tuple_from_vector_of_string (const std::vector<std::string> &v)
{
    return std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>(static_cast<uint8_t>(stoi(v.at(0))),
                                                          static_cast<uint8_t>(stoi(v.at(1))),
                                                          static_cast<uint8_t>(stoi(v.at(2))),
                                                          static_cast<uint8_t>(stoi(v.at(3))));
};

//std::ostream& operator<<(std::ostream& s, const std::vector<std::string>& vs)
//{
//    return s << vs.at(0) << "." << vs.at(1) << "." << vs.at(2) << "." << vs.at(3);
//}

using ip_type = std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>;
using ip_container = std::list<ip_type>;

namespace std {
    std::ostream &operator<<(std::ostream &os, const ip_type &ip) {

        os << std::get<0>(ip) << "."
           << std::get<1>(ip) << "."
           << std::get<2>(ip) << "."
           << std::get<3>(ip);
        return os;
    }
}

int main(int argc, char const *argv[])
{
    try
    {
        std::ifstream in("../in.txt");
        std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
        std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!

        std::ofstream out("out.txt");
        std::streambuf * coutbuf = std::cout.rdbuf();
        std::cout.rdbuf(out.rdbuf());

        ip_container ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.emplace_back(split<std::string,std::tuple<std::string>>(v.at(0), '.'));
        }

        // TODO reverse lexicographically sort

//        std::sort(std::begin(ip_pool),std::end(ip_pool));//,
//                  [](const std::vector<std::string> &a, const std::vector<std::string> &b)
//                  {
//                      uint32_t ip_a = 0, ip_b = 0;
//                      for(int i = 0; i < 4; ++i) {
//                          ip_a |= (unsigned char)std::stoi(a[i]) << (24 - (i*8));
//                          ip_b |= (unsigned char)std::stoi(b[i]) << (24 - (i*8));
//                      }
//                      return ip_a > ip_b;
//                  });

//        for(std::vector<std::vector<std::string> >::const_iterator ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
//        {
//            for(std::vector<std::string>::const_iterator ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
//            {
//                if (ip_part != ip->cbegin())
//                {
//                    std::cout << ".";
//                }
//                std::cout << *ip_part;
//            }
//            std::cout << std::endl;
//        }

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)

//    std::vector<std::vector<int>>::value_type
//        auto filter = [&](unsigned char byte){
//            std::copy_if(std::begin(ip_pool),std::end(ip_pool),
//                         std::ostream_iterator<decltype(*std::begin(ip_pool))>(std::cout),
//                         [byte](const ip_type & ip) {
//                             unsigned char first_byte = (unsigned char)stoi(ip.at(0));
//                             return (first_byte == byte);
//                         }
//            );
//        };
//        filter(1);

//        std::vector<std::vector<int>> a = {{1,2,3,4},{2,2,3,4}};
//        std::copy_if(std::begin(a),a.end(),std::ostream_iterator<typename std::vector<int>>(std::cout, "\n"),
//                     [](std::vector<int> g){return g[0]%2 == 0;}
//        );

       // filter(1);
//        std::cout << "sdads" << std::endl;
//        std::cout << ip_pool.at(1);

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46

        out.close();
        system("out.txt");
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }



    return 0;
}

namespace std {
    std::ostream &operator<<(std::ostream &s, const std::vector<int> &vs) {
        s << vs.at(0) << "." << vs.at(1) << "." << vs.at(2) << "." << vs.at(3);
        return s;
    }
}