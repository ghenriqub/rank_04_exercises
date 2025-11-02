


static node	*parse_expr_r(char **s)
{
	node	*left = parse_term(s);
	
	if (!left)
		return (NULL);
	while (accept(s, '+'))
	{
		node	*right = parse_term(s);
		if (!right)
		{
			destroy_tree(left);
			return (NULL);
		}
		node	n = { .type = ADD, .l = left, .r = right};
		left = new_node(n);
		if (!left)
			return (NULL);
	}
	return (left);
}
