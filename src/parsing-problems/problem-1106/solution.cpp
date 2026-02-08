/*
					1106. Parsing A Boolean Expression

A boolean expression is an expression that evaluates to either true or false. It can be in one of the following shapes:

't' that evaluates to true.
'f' that evaluates to false.
'!(subExpr)' that evaluates to the logical NOT of the inner expression subExpr.
'&(subExpr1, subExpr2, ..., subExprn)' that evaluates to the logical AND of the inner expressions subExpr1, subExpr2, ..., subExprn where n >= 1.
'|(subExpr1, subExpr2, ..., subExprn)' that evaluates to the logical OR of the inner expressions subExpr1, subExpr2, ..., subExprn where n >= 1.
Given a string expression that represents a boolean expression, return the evaluation of that expression.

It is guaranteed that the given expression is valid and follows the given rules.

*/


class Solution {
private:

    size_t find_end_bracket_pos(string const & expr, size_t start_pos)
    {
        std:stack<char> stck;
        for(size_t i = start_pos; i < expr.size(); i++)
        {
            if (expr[i] != '(' && expr[i] != ')')
                continue;
            
            if (expr[i] == '(') stck.push(expr[i]);
            else if (expr[i] == ')') stck.pop();
            
            if (stck.empty())
                return i;
        }
        return 0;
    }

    string cut_inner_func(string const & expr, size_t start_pos)
    {
        size_t end_pos = find_end_bracket_pos(expr, start_pos);
        start_pos += 2;
        return expr.substr(start_pos, end_pos - start_pos);
    }

    size_t make_offset(string const & inner_func)
    {
        return inner_func.size() + 2;
    }

    bool parse_or(string const & expr)
    {
        bool res = false;                
        size_t index = 0;
        string inner_func;
        
        if (expr.empty())
        {
            return true;
        }

        while (index < expr.size())
        {
            if (res)
                return true; 
            
            if (expr[index] == '&')
            {
                inner_func = cut_inner_func(expr, index);            
                res |= parse_and(inner_func);
                index += make_offset(inner_func);  
            }

            if (expr[index] == '|')
            {
                inner_func = cut_inner_func(expr, index);                                  
                res |= parse_or(inner_func);
                index += make_offset(inner_func); 
            }

            if (expr[index] == '!')
            {
                inner_func = cut_inner_func(expr, index);
                res |= parse_not(inner_func);
                index += make_offset(inner_func); 
            }
            
            if (expr[index] == 't')
            {
                res |= true;
                break;    
            }

            if (expr[index] == 'f')
            {
                res |= false; 
                index++;  
            } 
            else 
            {
                index++;
            }
        }           
    
        return res; 
    }

    bool parse_and(string const & expr)
    {
        bool res = true; 
        size_t index = 0;
        string inner_func;
        
        if (expr.empty())
        {
            return true;
        } 

        while (index < expr.size())
        {
            if (!res)
                return false;          
            
            if (expr[index] == '&')
            {
                inner_func = cut_inner_func(expr, index);
                res &= parse_and(inner_func);
                index += make_offset(inner_func);
            }

            if (expr[index] == '|')
            {
                inner_func = cut_inner_func(expr, index);                                      
                res &= parse_or(inner_func);
                index += make_offset(inner_func);
            }

            if (expr[index] == '!')
            {
                inner_func = cut_inner_func(expr, index);
                res &= parse_not(inner_func);
                index += make_offset(inner_func);
            }
            
            if (expr[index] == 't')
            {
                res &= true;    
            }

            if (expr[index] == 'f')
            {
                res &= false; 
                index++;  
                break;  
            } 
            else 
            {
                index++;
            }
        }           
        
        return res;
    }

    bool parse_not(string const & expr)
    {
        bool res;
        size_t start_pos = 0;
        if (expr.empty())
        {
            return true;
        }
        if (expr.size() == 1)
        {
            return expr == "f";
        }
        else
        {
            if (expr[start_pos] == '&')
            {
               res = parse_and(cut_inner_func(expr, start_pos));
            }    
            else if (expr[start_pos] == '|')
            {
                res = parse_or(cut_inner_func(expr, start_pos));
            }    
            else if (expr[start_pos] == '!')
            {
                res = parse_not(cut_inner_func(expr, start_pos));
            }
        }
        return !res;
    }    

public:
    bool parseBoolExpr(string expr) 
    {  
        bool res; 
        size_t start_pos = 0;
        switch (expr[start_pos])
        {
            case 't':
                res = true;
                break;
            case 'f':
                res = false;
                break;
            case '&':
                res = parse_and(cut_inner_func(expr, start_pos));
                break;
            case '|':
                res = parse_or(cut_inner_func(expr, start_pos));
                break;
            case '!':
                res = parse_not(cut_inner_func(expr, start_pos));
                break;
        }
        return res;
    }
};
