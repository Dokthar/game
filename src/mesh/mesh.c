#include <stdlib.h>
#include <string.h>
#include "mesh.h"

int mesh_unindex(struct Mesh* mesh) {
    float *vertices = NULL, *normals = NULL, *texCoords = NULL;
    unsigned int i, index;

    if ((mesh->numVertices && !(vertices = malloc(3 * mesh->numIndices * sizeof(float))))
     || (mesh->numNormals && !(normals = malloc(3 * mesh->numIndices * sizeof(float))))
     || (mesh->numTexCoords && !(texCoords = malloc(2 * mesh->numTexCoords * sizeof(float))))) {
        free(vertices);
        free(normals);
        free(texCoords);
        return 0;
    }

    for (i = 0; i < mesh->numIndices; i++) {
        index = mesh->indices[i];
        if (vertices) memcpy(vertices + 3 * i, mesh->vertices + 3 * index, 3 * sizeof(float));
        if (normals) memcpy(normals + 3 * i, mesh->normals + 3 * index, 3 * sizeof(float));
        if (texCoords) memcpy(texCoords + 2 * i, mesh->texCoords + 2 * index, 2 * sizeof(float));
    }

    free(mesh->vertices);
    free(mesh->normals);
    free(mesh->texCoords);
    free(mesh->indices);
    mesh->vertices = vertices;
    mesh->normals = normals;
    mesh->texCoords = texCoords;
    mesh->indices = NULL;
    mesh->numVertices = mesh->numIndices;
    mesh->numNormals = mesh->numIndices;
    mesh->numTexCoords = mesh->numIndices;
    mesh->numIndices = 0;

    return 1;
}

void mesh_free(struct Mesh* mesh) {
    free(mesh->vertices);
    free(mesh->normals);
    free(mesh->texCoords);
    free(mesh->indices);
}
