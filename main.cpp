#include <Application.h>

int main()
{
    Application application;

    while (application.isActive())
    {
        application.update();
    }

    return 0;
}
