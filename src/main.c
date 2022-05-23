#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main() {
    user_t *user_list = NULL;

    user_list = fetch_users(user_list);

    user_t *tmp = new_user("pietro", "smusi", "pietro", "smusi");
    user_list = add_to_list(user_list, tmp);

    update_user_list(user_list);

    return 0;
}