#include <stdio.h>
#include "link_disjoint_set.h"

int main()
{
    Node u = {NULL, "f", NULL};
    Node v = {NULL, "g", NULL};

    MAKE_SET(&u);
    MAKE_SET(&v);

    Set *s = UNION(&u, &v);

    return 0;
}
