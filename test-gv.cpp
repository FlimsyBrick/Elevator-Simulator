#include "ECGraphicViewImp.h"
#include "ElevatorObserver.h"

// Test graphical view code
int real_main(int argc, char **argv)
{
    //Size of Application
    const int widthWin = 600, heightWin = 1000;
    ECGraphicViewImp view(widthWin, heightWin, 10);
  
    // create a simple observer
    ECSimpleGraphicObserver obs(view);
    view.Attach(&obs);
    view.Show();
    
    return 0;
}

int main(int argc, char **argv)
{
    return real_main(argc, argv);
    //return al_run_main(argc, argv, real_main);
}

