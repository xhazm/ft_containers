/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase_key.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 13:39:14 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/18 14:22:16 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/map.hpp"
#include "../../inc/pair.hpp"
#include <iostream>
#include <string>

#define PRINT_ALL(map)  print_map(map);
#define PRINT_LINE(x,y) std::cout << x << y << std::endl;

void print_map(ft::map<int,std::string> map)
{
    ft::map<int,std::string>::iterator it = map.begin();
    for (; it != map.end(); ++it) 
    {
        std::cout << "K: " << it->first << std::endl;
        std::cout << "V: " << it->second << std::endl;
    }
    std::cout << "Size: " << map.size() << std::endl;
}

void print_map(ft::map<std::string,std::string> map)
{
    ft::map<std::string,std::string>::iterator it = map.begin();
    for (; it != map.end(); ++it) 
    {
        std::cout << "K: " << it->first << std::endl;
        std::cout << "V: " << it->second << std::endl;
    }
    std::cout << "Size: " << map.size() << std::endl;
}


void int_map()
{
     
        ft::map<int, std::string>::size_type size;
        ft::map<int, std::string> m;
        m.erase(m.begin(), m.end());

        m.insert(ft::make_pair(23, "23n"));
        m.insert(ft::make_pair(25, "asdasdfsdfsafdsf"));
        m.insert(ft::make_pair(1, "asdssdfdfdffffff"));
        m.insert(ft::make_pair(2, "dsfdffffdfdfdsdfdffa"));
        m.insert(ft::make_pair(3, "sssdfs"));
        m.insert(ft::make_pair(75, "dfse"));
        m.insert(ft::make_pair(30, "sefsadfasdfasdfsadfasdfsf"));
        m.insert(ft::make_pair(-22, "dfhkihgbnfbcx5reterjhd"));
        m.insert(ft::make_pair(-23, "sdffgdfgrefet34thfgheewt"));
        m.insert(ft::make_pair(0, "98y4rtuohwidsjusdossefsse"));

        size = m.erase(64);

        PRINT_LINE("Erased?:", size);
        PRINT_ALL(m);

        size = m.erase(0);

        PRINT_LINE("Erased?:", size);
        PRINT_ALL(m);

        size = m.erase(75);

        PRINT_LINE("Erased?:", size);
        PRINT_ALL(m);

        size = m.erase(1);

        PRINT_LINE("Erased?:", size);
        PRINT_ALL(m);

        size = m.erase(2);

        PRINT_LINE("Erased?:", size);
        PRINT_ALL(m);

        size = m.erase(3);

        PRINT_LINE("Erased?:", size);
        PRINT_ALL(m);

        size = m.erase(23);

        PRINT_LINE("Erased?:", size);
        PRINT_ALL(m);

        size = m.erase(23);

        PRINT_LINE("Erased?:", size);
        PRINT_ALL(m);

        size = m.erase(30);

        PRINT_LINE("Erased?:", size);
        PRINT_ALL(m);

        size = m.erase(-22);

        PRINT_LINE("Erased?:", size);
        PRINT_ALL(m);

        size = m.erase(-23);

        PRINT_LINE("Erased?:", size);
        PRINT_ALL(m);

        size = m.erase(-23);

        PRINT_LINE("Erased?:", size);
        PRINT_ALL(m);

        size = m.erase(25);

        PRINT_LINE("Erased?:", size);
        PRINT_ALL(m);

        size = m.erase(-23);

        PRINT_LINE("Erased?:", size);
        PRINT_ALL(m);

        size = m.erase(25);

        PRINT_LINE("Erased?:", size);
        PRINT_ALL(m);

}

void str_map()
{
        ft::map<std::string, std::string> m;

        ft::map<std::string, std::string>::size_type size = m.erase("");
        PRINT_LINE("Erased?:", size);
        PRINT_ALL(m);

        m.insert(ft::make_pair("", ""));
        m.insert(ft::make_pair("123", "kjhgfdsdffghsfghdfgh"));
        m.insert(ft::make_pair("1234", "gfdsadgg"));
        m.insert(ft::make_pair("123456789123456789123456789", "49857459898674568464"));
        m.insert(ft::make_pair("0", "2345456456456456"));
        m.insert(ft::make_pair("", ""));
        m.insert(ft::make_pair("", "9459845984598498"));
        m.insert(ft::make_pair("000000000000000000000000", "1111111111111111111111111111"));

        size = m.erase("1");

        PRINT_LINE("Erased?:", size);
        PRINT_ALL(m);

        size = m.erase("123");

        PRINT_LINE("Erased?:", size);
        PRINT_ALL(m);

        size = m.erase("123");

        PRINT_LINE("Erased?:", size);
        PRINT_ALL(m);

        size = m.erase("");

        PRINT_LINE("Erased?:", size);
        PRINT_ALL(m);

        size = m.erase("1234");

        PRINT_LINE("Erased?:", size);
        PRINT_ALL(m);

        size = m.erase("123456789123456789123456789");

        PRINT_LINE("Erased?:", size);
        PRINT_ALL(m);

        size = m.erase("000000000000000000000000");

        PRINT_LINE("Erased?:", size);
        PRINT_ALL(m);

        size = m.erase("0");

        PRINT_LINE("Erased?:", size);
        PRINT_ALL(m);

        size = m.erase("000000000000000000000000");

        PRINT_LINE("Erased?:", size);
        PRINT_ALL(m);
}
void map_test_erase_key()
{
    int_map();
    str_map();
}

