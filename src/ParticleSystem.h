// -*- mode: c++; coding: utf-8 -*-

// Linthesia

#ifndef __PARTICLE_SYSTEM_H
#define __PARTICLE_SYSTEM_H

#include "Renderer.h"
#include <vector>

struct Particle {
    float x, y;
    float vx, vy;
    float life; // 0.0 to 1.0
    int r, g, b;
    float size;
};

class ParticleSystem {
public:
    ParticleSystem();

    void Update();
    void Draw(Renderer &renderer) const;

    void Spawn(int x, int y, int r, int g, int b, int count = 10);

private:
    std::vector<Particle> m_particles;
};

#endif // __PARTICLE_SYSTEM_H
