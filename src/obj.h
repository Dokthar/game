#ifndef OBJ_H
#define OBJ_H

struct OBJ {
    float *vertices, *normals, *texCoords;
    struct OBJFace {
        struct OBJFaceElem {
            unsigned int v, t, n;
        } *elems;
        unsigned int numElems;
    } *faces;
    unsigned int numVertices, numNormals, numTexCoords, numFaces;
};

int obj_load(struct OBJ* obj, FILE* file);
void obj_free(struct OBJ* obj);

int obj_triangulate(struct OBJ* obj);

#endif