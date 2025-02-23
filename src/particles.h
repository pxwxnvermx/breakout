#ifndef __PARTICLES_H__
#define __PARTICLES_H__

#define NUM_PARTICLES 1000

#include "raylib.h"
#include "raymath.h"
#include "stdlib.h"
#include <raylib.h>

typedef struct {
  int active;
  Vector2 pos;
  Vector2 vel;
  int size_begin;
  int size_end;
  float lifetime;
  float life_remaining;
} Particle;

typedef struct {
  Particle particles_pool[NUM_PARTICLES];
  int pool_index;
} ParticleState;

void update_particles(ParticleState *particle_state, float delta) {
  for (size_t i = 0; i < NUM_PARTICLES; i++) {
    Particle *particle = &(particle_state->particles_pool[i]);
    if (particle->active == 0)
      continue;

    if (particle->life_remaining <= 0.0f) {
      particle->active = 0;
      continue;
    }

    particle->life_remaining -= delta;
    particle->pos.x += particle->vel.x * delta;
    particle->pos.y += particle->vel.y * delta;
  }
}

void draw_particles(ParticleState *particle_state) {
  for (size_t i = 0; i < NUM_PARTICLES; i++) {
    Particle particle = particle_state->particles_pool[i];
    float life = particle.life_remaining / particle.lifetime;
    Color color = Fade(ORANGE, life);
    int size = Lerp(particle.size_end, particle.size_begin, life);
    DrawCircleV(particle.pos, size, color);
  }
  return;
}

void emit_particle(ParticleState *particle_state, Particle p_props) {
  Particle *particle =
      &particle_state->particles_pool[particle_state->pool_index];
  particle->active = 1;
  particle->pos = p_props.pos;
  particle->size_begin = p_props.size_begin;
  particle->size_end = p_props.size_end;
  particle->vel = p_props.vel;
  // particle->vel = (Vector2){
  //     particle->size_begin * 10.0f - GetRandomValue(0, 100) * 0.5f,
  //     particle->size_begin * 10.0f - GetRandomValue(0, 100) * 0.5f,
  // };
  particle->lifetime = p_props.lifetime;
  particle->life_remaining = p_props.life_remaining;

  particle_state->pool_index--;
  if (particle_state->pool_index < 0) {
    particle_state->pool_index = NUM_PARTICLES - 1;
  }
}

#endif // !__PARTICLES_H__
