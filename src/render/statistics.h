#ifndef STATISTICS_H
#define STATISTICS_H

struct Statistics {
    unsigned int nbTriangles;
    unsigned int nbVertices;
    unsigned int nbUniformsSet;

    unsigned int nbShaderSwitches;
    unsigned int nbShaderFrame;
    unsigned int nbShaderMemory;

    unsigned int nbTextureSwitches;
    unsigned int nbTextureFrame;
    unsigned int nbTextureMemory;

    unsigned int nbFboSwitches;
    unsigned int nbFboFrame;
    unsigned int nbFboMemory;
};

#endif
