/*
							1071. Greatest Common Divisor of Strings

For two strings s and t, we say "t divides s" if and only if s = t + t + t + ... + t + t (i.e., t is concatenated with itself one or more times).

Given two strings str1 and str2, return the largest string x such that x divides both str1 and str2.

*/

class Solution {
private:
    void swap(string & str1, string & str2)
    {
        string temp = str1;
        str1 = str2;
        str2 = temp;
    }

    void check_and_incr(size_t & sub_str_index, size_t sub_str_size)
    {
       sub_str_index = sub_str_index >= sub_str_size - 1 ? 0 : sub_str_index + 1;
    }
    
    string remove_sub_str(string & str, string const & sub_str)
    {
        size_t str_slow_index = 0;
        size_t str_fast_index = 0;
        size_t sub_str_index = 0;
        while (str_fast_index < str.size())
        {
            if (str[str_fast_index] != sub_str[sub_str_index])
            {
                if (sub_str_index != 0)
                {
                    str_slow_index += sub_str_index;
                    sub_str_index = 0;
                }
                str[str_slow_index++] = str[str_fast_index++];
            }
            else 
            {
                str_fast_index++;
                check_and_incr(sub_str_index, sub_str.size());
            }
        }

        if (sub_str_index != 0)
        {
            str_fast_index -= sub_str_index;
            while (str_fast_index < str.size())
            {
                str[str_slow_index++] = str[str_fast_index++];
            }         
        }
        return str.substr(0, str_slow_index);
    }

    string get_remainder(string & str1, string const & str2)
    {
        string res = remove_sub_str(str1, str2);
        if (res == str1)
            return "-1";
        else
            return res;  
    }
public:
    string gcdOfStrings(string str1, string str2) 
    {
        string temp = "";
        while (str2 != "")
        {
            if (str1.size() < str2.size()) swap(str1, str2);

            temp = get_remainder(str1, str2);
            if (temp == "-1") return "";
            str1 = str2;
            str2 = temp;
        }
        return str1;
    }
};