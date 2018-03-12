#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <stdio.h>

struct Asset_Manager {
    const char** assets_path;
};

void init_asset_manager(const char* path[]);

FILE* fopen_asset(const char* asset, const char* mode);

struct Asset_Manager* new_asset_manager(const char* path[], struct Asset_Manager* am);

#endif
