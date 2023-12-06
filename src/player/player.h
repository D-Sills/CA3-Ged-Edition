
#include "../components/cmp_character.h"

class player : public cmp_character {
public:
    player() = delete;
    explicit player(Entity* p);

    void update(double dt) override;
    void render() override;
    ~player() override = default;

    void attack(double dt) override;

    void move(const double dt, const float dir_x, const float dir_y);
};
