#ifndef ElevatorObserver_h
#define ElevatorObserver_h

#include "ECObserver.h"
#include "ECGraphicViewImp.h"


//************************************************************
class ECSimpleGraphicObserver : public ECObserver
{
public:
    ECSimpleGraphicObserver( ECGraphicViewImp &viewIn );
    virtual void Update();
    
private:
    ECGraphicViewImp &view;
    bool fIsSpaceBarPressed;
    bool fIsUpKeyPressed;
    bool fIsDownKeyPressed;
    bool fIsLeftKeyPressed;
    bool fIsRightKeyPressed;
};

bool is_point_in_triangle(int px, int py, int x1, int y1, int x2, int y2, int x3, int y3);

#endif /* SimpleObserver_h */
