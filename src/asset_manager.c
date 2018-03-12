#include "asset_manager.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

struct Asset_Manager global_am = {0};

void init_asset_manager(const char* path[]) {
    global_am.assets_path = path;
}

struct Asset_Manager* new_asset_manager(const char* path[], struct Asset_Manager* am) {
    struct Asset_Manager* ret;

    if (!am) {
	ret = malloc(sizeof(struct Asset_Manager));
    } else {
	ret = am;
    }
    ret->assets_path = path;

    return ret;
}

FILE* fopen_asset(const char* asset, const char* mode) {
    const char** path = global_am.assets_path;
    char* asset_path = NULL;
    int a_len, p_len;
    FILE* file = NULL;

    /* first try to open the asset */
    file = fopen(asset, mode);
    if (!file) {
	if (errno != ENOENT) {
	    fprintf(stderr, "Failed to open asset: %s (%s)", asset, strerror(errno));
	}
    }

    if (path != NULL && file == NULL) {
	a_len = strlen(asset);
	for (; *path != NULL && file == NULL; path++) {
	    /* str cat */
	    p_len = strlen(*path);
	    asset_path = realloc(asset_path, (a_len + p_len + 1) * sizeof(char));
	    strcpy(asset_path, *path);
	    strcpy(asset_path + p_len, asset);

	    file = fopen(asset_path, mode);
	    if (!file) {
		if (errno != ENOENT) {
		    fprintf(stderr, "Failed to open asset: %s (%s)", asset, strerror(errno));
		}
	    }
	    fflush(stdout);
	}
	free(asset_path);
    }
    return file;
}
