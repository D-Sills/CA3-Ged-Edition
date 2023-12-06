#include "engine.h"

class LoadingScreen {
public:
    LoadingScreen() = default;
    ~LoadingScreen() = default;
    static void Update(float dt, const Scene* scn);
    static void Render();
    static void Load();
    static bool IsLoading();
    void SetLoading(bool);
};
