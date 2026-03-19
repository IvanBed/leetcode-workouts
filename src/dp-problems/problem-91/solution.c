/*

91. Decode Ways

You have intercepted a secret message encoded as a string of numbers. The message is decoded via the following mapping:

"1" -> 'A'

"2" -> 'B'

...

"25" -> 'Y'

"26" -> 'Z'

However, while decoding the message, you realize that there are many different ways you can decode the message because some codes are contained in other codes ("2" and "5" vs "25").

For example, "11106" can be decoded into:

"AAJF" with the grouping (1, 1, 10, 6)
"KJF" with the grouping (11, 10, 6)
The grouping (1, 11, 06) is invalid because "06" is not a valid code (only "6" is valid).
Note: there may be strings that are impossible to decode.

Given a string s containing only digits, return the number of ways to decode it. If the entire string cannot be decoded in any valid way, return 0.

The test cases are generated so that the answer fits in a 32-bit integer.
*/

bool valid_one_digit_num(char *s, size_t index)
{
    if ('0' < s[index] && s[index] <= '9')
    {
        return true;
    }    
    else 
        return false;
}

bool valid_two_digit_num(char *s, size_t index)
{
    printf("%c %c\n", s[index - 1], s[index]);
    if (('1' <= s[index - 1]  && s[index - 1] < '3') && ('0' <= s[index] && s[index] < '7'))
    {
        return true;
    }    
    else 
        return false;
}

void init_dp_arr(int *dp, char *s, size_t str_len)
{
    if (str_len == 1)
	{
        if (valid_one_digit_num(s, 0))
		    dp[0] = 1;
	    else 
			dp[0] = 0;
	}
	else 
	{
		if (valid_two_digit_num(s, 1))
		{
			dp[0] = 1;
            dp[1] = 2;
		}
		else 
		{
			dp[0] = 1;
            dp[1] = 1;
		}	
	}
}

int numDecodings(char *s) 
{
    size_t str_len = strlen(s);
	if (str_len == 0)
		return -1;
	
    int *dp = (int*) malloc(str_len * sizeof(int));
	
	init_dp_arr(dp, s, str_len);
	

    for (size_t i = 2; i < str_len; i++)
    {
        if (valid_two_digit_num(s, i))
		{
            dp[i] = dp[i - 1] + dp[i - 2];			
		}
        else
		{
            if (valid_one_digit_num(s, i))
			    dp[i] = dp[i - 1];	
			else 
                return 0;				
		}
    }
    
    return dp[str_len - 1];
}