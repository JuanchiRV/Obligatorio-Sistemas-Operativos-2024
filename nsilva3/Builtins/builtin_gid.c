#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <grp.h>
#include <error.h>
#include <errno.h>
#include "wrappers.h"
#include "minish.h"
#define MAX_GROUPS 500

int
builtin_gid(int argc, char **argv)
{
    if(argc == 1 && strcmp(argv[0], "gid") == 0)
    {
        ;
    }
    gid_t group_id = getgid();
    char *username = getlogin();
    fprintf(stderr, "Real Gid: %d(%s)\n", (int) group_id, username);
    gid_t groups_list[MAX_GROUPS];
    int num_group = getgroups(MAX_GROUPS, groups_list);
    if (num_group < 0){
        error(ERROR, errno, "No se pudo acceder a los grupos\n");
        return EXIT_FAILURE;
    }
    fprintf(stderr,"Groups: ");
    for (int i=0; i<num_group;i++){
        struct group *grp = getgrgid(groups_list[i]);
        if (grp != NULL){
            fprintf(stderr, "%d (%s) ",grp->gr_gid,grp->gr_name);
        }
    }
    printf("\n");
    return EXIT_SUCCESS;
}
