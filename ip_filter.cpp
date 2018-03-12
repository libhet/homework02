#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

// = = = = = = = = = =
#include <fstream>
#include <algorithm>
#include <iterator>

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

std::ostream& operator<<(std::ostream& s, const std::vector<std::string>& vs)
{
    return s << vs.at(0) << "." << vs.at(1) << "." << vs.at(2) << "." << vs.at(3);
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

        std::vector<std::vector<std::string> > ip_pool;


        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        // TODO reverse lexicographically sort
        std::sort(ip_pool.begin(),ip_pool.end(),
                  [](const std::vector<std::string> &a, const std::vector<std::string> &b)
                  {
                      uint32_t ip_a = 0, ip_b = 0;
                      for(int i = 0; i < 4; ++i) {
                          ip_a |= (unsigned char)std::stoi(a[i]) << (24 - (i*8));
                          ip_b |= (unsigned char)std::stoi(b[i]) << (24 - (i*8));
                      }
                      return ip_a > ip_b;
                  });

        for(std::vector<std::vector<std::string> >::const_iterator ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
        {
            for(std::vector<std::string>::const_iterator ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
            {
                if (ip_part != ip->cbegin())
                {
                    std::cout << ".";
                }
                std::cout << *ip_part;
            }
            std::cout << std::endl;
        }

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)
//        auto filter = [&](unsigned char x){
//            std::copy_if(ip_pool.cbegin(), ip_pool.cend(),
//                      std::ostream_iterator<std::vector<std::string>>(std::cout, "/n"),
//                         [&](const std::vector<std::string> & v)
//                         {
//                         return (stoi(v.at(0)) == x);
//                         });
//        };
//        filter(1);
        std::cout << "sdads" << std::endl;
        std::cout << ip_pool.at(1);

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

