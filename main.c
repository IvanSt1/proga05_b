#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct Item {
    char c;
    struct Item *next;
} Item;
Item *deleteList(Item *ptr) {
    Item *tmp = NULL;
    while (ptr != NULL) {
        tmp = ptr;
        ptr = ptr->next;
        free(tmp);
    }
    return ptr;
}

Item *reorg(Item *p) {
    char *mas16[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    Item head = {'*', p};
    Item *cur = &head, *prev = &head;
    Item *s, *a;
    Item *pr;
    Item head1 = {'*', NULL};
    Item *last1 = &head1;
    cur = cur->next;
    s = cur;
    int len = 0, ost, x, k = 0;
    while (cur) {
        if ((cur->c != ' ')&&(cur->c!='\t') ) {
            len++;
            cur = cur->next;
        } else {
            a = cur;
            cur = s;
            ost = len % 4;
//101
            if (ost != 0) {
                for (int i = 0; i < (ost); i++) {
                    if (cur->c == '0')
                        x = 0;
                    else
                        x = 1;
                    if (i == ost - 1)
                        k = k + x;
                    else
                        k = k * 2 + x * 2;

                    cur = cur->next;
                }

                last1->next = (Item *) malloc(sizeof(Item));
                last1 = last1->next;
                last1->c = mas16[k];
                k = 0;
            }

            for (int i = 0; i < (len / 4); i++) {
                for (int j = 0; j < 4; j++) {
                    if (cur->c == '0')
                        x = 0;
                    else
                        x = 1;
                    if (j == 3)
                        k = k + x;
                    else
                        k = k * 2 + x * 2;
                    cur = cur->next;
                }
                last1->next = (Item *) malloc(sizeof(Item));
                last1 = last1->next;
                last1->c = mas16[k];
                k = 0;
            }
            len = 0;
            last1->next = (Item *) malloc(sizeof(Item));
            last1 = last1->next;
            last1->c = cur->c;
            cur=cur->next;

        }


    }
    pr = head1.next;
    if (prev->next) {
        free(prev->next);
        prev->next = NULL;
    }
    return pr;
}

int getList(Item **pptr) {
    char buf[21], *str;
    Item head = {'*', NULL};
    Item *last = &head;
    int n, rc = 1;
    do {
        n = scanf("%20[^\n]", buf);
        if (n < 0) {
            deleteList(head.next);
            head.next = NULL;
            rc = 0;
            continue;
        }
        if (n > 0) {
            for (str = buf; *str != '\0'; ++str) {
                last->next = (Item *) malloc(sizeof(Item));
                last = last->next;
                last->c = *str;
            }
            last->next = NULL;
        } else
            scanf("%*c");
    } while (n > 0);
    *pptr = head.next;
    return rc;
}

void putList(const char *msg, Item *ptr) {
    printf("%s: \"", msg);
    for (; ptr != NULL; ptr = ptr->next)
        printf("%c", ptr->c);
    printf("\"\n");
}

int main() {
    Item *st = NULL;
    char *str;
    while (puts("enter string"), getList(&st)) {
        putList("Source string", st);
        st = reorg(st);
        putList("New string", st);
        st = deleteList(st);
    }

    return 0;
}
