// -*- mode: c++; coding: utf-8 -*-

// Linthesia

#include "ParticleSystem.h"
#include <cstdlib>
#include <cmath>

ParticleSystem::ParticleSystem() {}

void ParticleSystem::Update() {
    for (auto it = m_particles.begin(); it != m_particles.end();) {
        it->x += it->vx;
        it->y += it->vy;
        it->vy -= 0.5f; // Gravity (falling down in inverted coords? Wait, Y=0 is bottom in GL? No, top-left is usually 0,0 in SDL, but GameState flips it?)
        // GameStateManager::Draw uses glScalef(1, -1, 1), so Y increases Upwards?
        // Let's assume standard physics: gravity pulls Y down. If Y+ is Up, vy -= g.

        it->life -= 0.02f;

        if (it->life <= 0) {
            it = m_particles.erase(it);
        } else {
            ++it;
        }
    }
}

void ParticleSystem::Draw(Renderer &renderer) const {
    for (const auto& p : m_particles) {
        int alpha = (int)(p.life * 255);
        renderer.SetColor(p.r, p.g, p.b, alpha);
        renderer.DrawQuad((int)p.x, (int)p.y, (int)p.size, (int)p.size);
    }
}

void ParticleSystem::Spawn(int x, int y, int r, int g, int b, int count) {
    for (int i = 0; i < count; ++i) {
        Particle p;
        p.x = (float)x;
        p.y = (float)y;

        // Random velocity
        float angle = ((rand() % 360) * 3.14159f) / 180.0f;
        float speed = (float)(rand() % 5 + 2);

        p.vx = cos(angle) * speed;
        p.vy = sin(angle) * speed;

        p.life = 1.0f;
        p.r = r; p.g = g; p.b = b;
        p.size = (float)(rand() % 4 + 2);

        m_particles.push_back(p);
    }
}
