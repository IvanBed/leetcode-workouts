/*
					22. Generate Parentheses

	Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
*/

void generateParenthes(vector<string> & store, string cur_str, int open_cntr, int close_cntr, int n)
{
	if (open_cntr < n)
		generateParenthes(store, cur_str + "(", open_cntr + 1, close_cntr, n);

	if (close_cntr < open_cntr)
		generateParenthes(store, cur_str + ")", open_cntr, close_cntr + 1, n);
		
	if (open_cntr == close_cntr && cur_str.size() == 2*n)
		store.push_back(cur_str);
}


vector<string> generateParenthesis(int n) 
{
	string cur_str = "(";
	vector<string> res;
	int open_cntr = 1;
	int close_cntr = 0;
	generateParenthes(res, cur_str, open_cntr, close_cntr, n);
	return res;
}
