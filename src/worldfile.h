#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

inline bool ParseWorldFile(const std::string &path,
                           double &ulLon, double &ulLat,
                           double &lrLon, double &lrLat)
{
    std::ifstream f(path);
    if(!f.is_open()) return false;

    double A, D, B, E, C, F; // world‑file params
    f >> A >> D >> B >> E >> C >> F;

    // A = pixelSizeX, E = -pixelSizeY
    // C,F = coord coin centre pixel haut‑gauche
    ulLon = C;
    ulLat = F;

    // Taille image pour calcul bas‑droit → ici exemple fixe 1000×1000, à ajuster dynamiquement
    int imgW = 1000, imgH = 1000;
    lrLon = C + A * imgW;
    lrLat = F + E * imgH;
    return true;
}
