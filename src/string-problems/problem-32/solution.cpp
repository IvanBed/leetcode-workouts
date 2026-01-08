/*
				32. Longest Valid Parentheses

Given a string containing just the characters '(' and ')', return the length of the longest valid (well-formed) parentheses substring.

*/

class Bracket
{
private:

    size_t _pos;
    char _val;

public:
    Bracket(size_t pos, char val)
    {
        _pos = pos;
        _val = val;
    }
    size_t get_pos() const
    {
        return _pos;
    }
};


class GoodBrackets
{
    size_t _start;
    size_t _end;

public:
    GoodBrackets(size_t start, size_t end)
    {
        _start = start;
        _end = end;
    }

    size_t get_start() const
    {
        return _start;
    }

    size_t get_end() const
    {
        return _end;
    }

    size_t get_size() const 
    {
        if (_start == 0  && _end == 0)
            return 0;

        return _end - _start + 1;
    }
};

class Solution 
{
private:

    int get_max(vector<GoodBrackets> const & brackets_store)
    {
        int max = 0;
        vector<int> accumulated_sizes(brackets_store.size(), 0);
        accumulated_sizes[0] = 0;
        for (size_t i = 1; i < brackets_store.size(); i++)
        {
            if (brackets_store[i].get_start() - 1 == brackets_store[i - 1].get_end())
            {
                accumulated_sizes[i] = accumulated_sizes[i - 1] + brackets_store[i].get_size();
            } 
            else 
            {
                accumulated_sizes[i] = brackets_store[i].get_size();
            }  
            if (accumulated_sizes[i] > max)
                max = accumulated_sizes[i];          
        }

        return max;
    }

    void remove_intesections(vector<GoodBrackets> & brackets_store, GoodBrackets const & cur)
    {
        size_t index = brackets_store.size() - 1;

        while (index > 0 && brackets_store[index].get_end() >= cur.get_start())
        {
            brackets_store.pop_back();
            index--;
        }
    }

public:
    
    int longestValidParentheses(string s) 
    {
        vector<GoodBrackets> brackets_store;
        brackets_store.push_back(GoodBrackets(0, 0));
        stack<Bracket> st;
        for (size_t i = 0; i < s.size(); i++)
        {
            if (s[i] == '(')
            {
                st.push(Bracket(i, s[i]));
                continue;
            }

            if (!st.empty() && s[i] == ')')
            {
                GoodBrackets cur_gb(st.top().get_pos(), i);
                remove_intesections(brackets_store, cur_gb);
                brackets_store.push_back(cur_gb);
                st.pop();
            }
        }

        return get_max(brackets_store);
    }
};