
static node *parse_factor(char **s)
{
    if (isdigit((unsigned char)**s))
    {
        node    n = { .type = VAL, .val = **s, .l = NULL, .r = NULL };
        (*s)++;
        return(new_node(n));
    }
    if (accept(s, '('))
    {
        node *e = parse_expr_r(s);
        if (!e)
            return (NULL);
        if (!expected(s, ')'))
        {
            destroy_tree(e);
            return (NULL);
        }
        return (e);
    }
    unexpected(**s);
    return(NULL);
}

static node *parse_term(char **s)
{
    node    *left = parse_factor(s);

    if (!left)
        return (NULL);
    while (accept(s, '*'))
    {
        node    *right = parse_factor(s);
        if (!right)
        {
            destroy_tree(left);
            return (NULL);
        }
        node    n = { .type = MULTI, .l = left, .r = right };
        left = new_node(n);
        if (!left)
            return (NULL);
    }
    return (left);
}

static char *parse_expr_r(char **s)
{
    node    *left = parse_term(s);

    if (!left)
        return (NULL);
    while (accept(s, '+'))
    {
        node    *right = parse_term(s);
        if (!right)
        {
            destroy_tree(left);
            return (NULL);
        }
        node    n = { .type = ADD, .l = left, .r = right };
        left = new_node(n);
        if (!left)
            return (NULL);
    }
    return (left);
}
