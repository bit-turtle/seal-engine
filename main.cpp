#include "engine.hpp"

void init();

void frame(seal::Time deltatime, seal::Input input);

int main() {
	seal::setinitfunc(init);
	seal::setframefunc(frame);
	seal::start(800,600,"Seal Engine Game");
	return 0;	
}

class Box : public seal::Sprite {
	public:
	Box() {
		hitbox.x = 10;
		hitbox.y = 10;
		hitbox.z = 10;
	}
	void frame(seal::Time deltatime, seal::Input input) {
		position.x += 1 * deltatime;
	}
};

void init() {
	seal::createSprite(new Box());
}

void frame(seal::Time deltatime, seal::Input input) {

}
