#include <stdio.h>
#include "tree_disjoint_set.h"

int main()
{
    Node u, v;
    u.data = "f";
    v.data = "g";

    MAKE_SET(&u);
    MAKE_SET(&v);

    UNION(&u, &v);

    return 0;
}
