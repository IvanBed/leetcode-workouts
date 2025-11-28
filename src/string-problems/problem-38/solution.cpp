/*

The count-and-say sequence is a sequence of digit strings defined by the recursive formula:

countAndSay(1) = "1"
countAndSay(n) is the run-length encoding of countAndSay(n - 1).
Run-length encoding (RLE) is a string compression method that works by replacing consecutive identical characters (repeated 2 or more times) with the concatenation of the character and the number marking the count of the characters (length of the run). For example, to compress the std::string "3322251" we replace "33" with "23", replace "222" with "32", replace "5" with "15" and replace "1" with "11". Thus the compressed std::string becomes "23321511".

Given a positive integer n, return the nth element of the count-and-say sequence.

*/

#include <map>
#define UTF8_OFFSET 48
#define COMPRESSED_STR(cnt, pos) std::string(1, digitToChar(cnt)) + std::string(1, num_str[pos])

class Solution {

private:

    char digitToChar(size_t digit)
    {
        return char (digit + UTF8_OFFSET);
    }

    std::string generateString(std::string const & num_str)
    {
        std::string res = "";
        size_t cnt = 1;
        for (size_t i = 1; i < num_str.size(); i++)
        {
            if (num_str[i] == num_str[i - 1]) 
            {
                cnt++;
            }
            else 
            {
                res += COMPRESSED_STR(cnt, i - 1);
                cnt = 1;
            }
        }
        res += COMPRESSED_STR(cnt, num_str.size() - 1);
        return res;
    }

public:
    std::string countAndSay(int n) 
    {
        std::string base = "1";
        for (size_t i = 1; i < n; i++)
        {
            base = generateString(base);
        }

        return base;
    }
};