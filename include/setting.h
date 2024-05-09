#pragma once
#include "global_stuff.h"

// ZOMBIE
int read_zombie_damage_from_file(SpriteType sprite_type);
int read_zombie_health_from_file(SpriteType sprite_type);
int read_zombie_hit_rate_from_file(SpriteType sprite_type);
int read_zombie_speed_from_file(SpriteType sprite_type);

// PLANT
int read_plant_damage_from_file(SpriteType sprite_type);
int read_plant_health_from_file(SpriteType sprite_type);
int read_plant_cooldown_from_file(SpriteType sprite_type);
int read_plant_hit_rate_from_file(SpriteType sprite_type);
int read_plant_speed_from_file(SpriteType sprite_type);
int read_plant_price_from_file(SpriteType sprite_type);

// ATTACK
int read_total_attack_time();
int read_attack_interval();
int read_first_interval_zombies();
int read_zombie_number_change();

// SUN
int read_sun_speed_from_file();
int read_sun_interval_from_file();