#include "SimpleObserver.h"

ECSimpleGraphicObserver :: ECSimpleGraphicObserver( ECGraphicViewImp &viewIn ) : view(viewIn), 
    fIsSpaceBarPressed(false), 
    fIsUpKeyPressed(false), 
    fIsDownKeyPressed(false),
    fIsLeftKeyPressed(false),
    fIsRightKeyPressed(false){}


void ECSimpleGraphicObserver :: Update(){
    ECGVEventType evt = view.GetCurrEvent();
    //Elevator Controlls
    if (evt == ECGV_EV_KEY_DOWN_UP) {
        fIsUpKeyPressed = true;
        //view.SetRedraw(true);
    }
    if (evt == ECGV_EV_KEY_DOWN_DOWN) {
        fIsDownKeyPressed = true;
        //view.SetRedraw(true);
    } 
    if (evt == ECGV_EV_KEY_UP_SPACE) {
        fIsSpaceBarPressed = true;
        view.SetRedraw(true);
    }

    //Buttons
    
    if (evt == ECGV_EV_MOUSE_BUTTON_DOWN) {
        int mouse_x, mouse_y;
        view.GetCursorPosition(mouse_x, mouse_y);
        for (int i = 0; i < view.floor; i++) {
            // Up Triangle Coordinates
            int up_x1 = view.x1, up_y1 = view.y1u - i * view.size;
            int up_x2 = view.x2, up_y2 = view.y2u - i * view.size;
            int up_x3 = view.x3, up_y3 = view.y3u - i * view.size;

            // Down Triangle Coordinates
            int down_x1 = view.x1, down_y1 = view.y1d - i * view.size;
            int down_x2 = view.x2, down_y2 = view.y2d - i * view.size;
            int down_x3 = view.x3, down_y3 = view.y3d - i * view.size;
            if (is_point_in_triangle(mouse_x, mouse_y, up_x1, up_y1, up_x2, up_y2, up_x3, up_y3)) {
                view.buttonPressedUp[i] = true;
            }

            // Check if "Down" button is clicked
            if (is_point_in_triangle(mouse_x, mouse_y, down_x1, down_y1, down_x2, down_y2, down_x3, down_y3)) {
                view.buttonPressedDown[i] = true;
            }
        }
    }
    

    //Passenger Controlls
    if (evt == ECGV_EV_KEY_UP_LEFT ){
        fIsLeftKeyPressed = true;
        view.SetRedraw(true);
    }
    if (evt == ECGV_EV_KEY_UP_RIGHT){
        fIsRightKeyPressed = true;
        view.SetRedraw(true);
    }


    if( evt == ECGV_EV_TIMER ){
        //Moving Elevator Up
        if (fIsUpKeyPressed && !view.stop) {
            if (view.target == -1) {view.target = view.yE2 - view.size;}
            if (view.target < 10) { view.target = view.yE2; }
            if (view.yE2 > view.target) {
                view.yE2 -= 2;
                view.SetRedraw(true);
            } else {
                view.target = -1;
                fIsUpKeyPressed = false;
            }
        }
        //Moving Elevator Down
        if (fIsDownKeyPressed && !view.stop) {
            if (view.target == -1) {view.target = view.yE2 + view.size;}
            if (view.target > 990) { view.target = view.yE2; }
            if (view.yE2 < view.target) {
                view.yE2 += 2;
                view.SetRedraw(true);
            } else {
                view.target = -1;
                fIsDownKeyPressed = false;
            }
        }
        //(Un)Pausing Elevator Action
        if (fIsSpaceBarPressed){
            view.stop = !view.stop;
            fIsSpaceBarPressed = false;
        }

        //Passenger Pickup/Dropoff/Spawning
        if(fIsRightKeyPressed && view.stop){
            int i = view.floor - view.yE2/view.size;
            //Offload Code
            view.passenger[i] = true;
            view.load = false;
            fIsRightKeyPressed = false;
        }
        if(fIsLeftKeyPressed && view.stop){ //Needs to stop first to pick up passenger
            int i = view.floor - view.yE2/view.size;
            if (view.buttonPressedUp[i] || view.buttonPressedDown[i]){
                view.buttonPressedUp[i] = false;
                view.buttonPressedDown[i] = false;
                view.passenger[i] = false;
                view.load = true;
            }
            fIsLeftKeyPressed = false;
        }
    }
}


bool is_point_in_triangle(int px, int py, int x1, int y1, int x2, int y2, int x3, int y3) {
    float d1, d2, d3;
    bool has_neg, has_pos;

    d1 = (px - x2) * (y1 - y2) - (x1 - x2) * (py - y2);
    d2 = (px - x3) * (y2 - y3) - (x2 - x3) * (py - y3);
    d3 = (px - x1) * (y3 - y1) - (x3 - x1) * (py - y1);

    has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}
