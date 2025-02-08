// Seal Engine Sprite2D Implementation
#include <seal/Sprite.hpp>

#include <map>

unsigned nextID = 0;

std::map<unsigned, Sprite2D*> spriteMap2D;

unsigned addSprite2D(Sprite2D* sprite) {
    unsigned id = nextID;
    spriteMap2D.insert( { id, sprite } );
    nextID++;
    return id;
}

std::optional<Sprite2D*> getSprite2D(unsigned id) {
    std::map<unsigned, Sprite2D*>::iterator it = spriteMap2D.find(id);
    if (it != spriteMap2D.end()) return std::optional<Sprite2D*>{it->second};
    else return std::nullopt;
}
