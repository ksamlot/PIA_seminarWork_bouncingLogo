#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <iostream>
#include <vector>
#include <string>

#include "findLCM.h"


int SCREEN_WIDTH;
int SCREEN_HEIGHT;

int main() {
    //Initialize Allegro
    if (!al_init()) {
        std::cerr << "Failed to initialize Allegro!" << std::endl;
        return 1;
    }

    //Initialize module for rendering
    if (!al_init_primitives_addon()) {
        std::cerr << "Failed to initialize primitives addon!" << std::endl;
        return 1;
    }

    //Initialize module for image input
    if (!al_init_image_addon()) {
        std::cerr << "Failed to initialize image addon!" << std::endl;
        return 1;
    }
    
    //Console input dimensions of screen
    std::cout << "Zadej sirku obrazovky (doporuceno 800):" << std::endl;
    std::cin >> SCREEN_WIDTH;
    std::cout << "Zadej vysku obrazovky (doporuceno 600):" << std::endl;
    std::cin >> SCREEN_HEIGHT;

    //Create diplay
    ALLEGRO_DISPLAY* display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!display) {
        std::cerr << "Failed to create display!" << std::endl;
        return 1;
    }

    //Load images
    ALLEGRO_BITMAP* logo1 = al_load_bitmap("./lev_cerna.png");
    ALLEGRO_BITMAP* logo2 = al_load_bitmap("./lev_modra.png");
    ALLEGRO_BITMAP* logo3 = al_load_bitmap("./lev_cervena.png");
    ALLEGRO_BITMAP* logo4 = al_load_bitmap("./lev_ruzova.png");
    ALLEGRO_BITMAP* logo5 = al_load_bitmap("./lev_zelena.png");
    ALLEGRO_BITMAP* logo6 = al_load_bitmap("./lev_zluta.png");
    ALLEGRO_BITMAP* logoFin = al_load_bitmap("./final.png");

    if (!logo1 || !logo2) {
        std::cerr << "Failed to load images!" << std::endl;
        al_destroy_display(display);
        return 1;
    }

    //Initialize position and speed of movement
    float x = 0;
    float y = 0;
    float speedX = 0.02;
    float speedY = 0.02;

    bool logoChanged = false;

    //Calculate prediction of number of noucnes until corner hit
    int diffScreenLogoH = SCREEN_HEIGHT - al_get_bitmap_height(logo1); //Calculate height difference of screen and image
    int diffScreenLogoW = SCREEN_WIDTH - al_get_bitmap_width(logo1); //Calculate width difference of screen and image

    std::cout << "Velikost obrazovky: " << SCREEN_WIDTH << "x" << SCREEN_HEIGHT << std::endl;

    int numberOfSteps = FindLCM::calculateLCM(diffScreenLogoH, diffScreenLogoW); //Find Least Common Multiple equal to the number of steps until corner hit
    int widthOfExtraDomain = numberOfSteps / diffScreenLogoW; //Calculate number of domains (series of reflections) - width (see https://lostmathlessons.blogspot.com/2016/03/bouncing-dvd-logo.html)
    int heightOfExtraDomain = numberOfSteps / diffScreenLogoH; //Calculate number of domains (series of reflections) - height
    int numberOfBouncesToCorner = widthOfExtraDomain + heightOfExtraDomain - 1; //Calculate number of bounces until image hits corner

    std::cout << "Pocet odrazu do narazu do rohu: " << numberOfBouncesToCorner << std::endl;
    
    //int intValue;

     
    int zero = 0; //Helper zero
    int numberOfBounces = 0; //Number of bounces in visualisation between corner hits
    int overallNumberOfBounces = 0; //Overall number of bounces in visualisation
    int endImageChange = 1;
 
    while (true) {
        //Set background color
        al_clear_to_color(al_map_rgb(255, 255, 255));

        //Move image
        x += speedX;
        y += speedY;

        //Collision with boundaries
        if (x < 0) { //Left boundray
            x = zero; //Reset x position to boundary limit
            speedX = -speedX; //Reverse direction of move in X

        }
        else if (x > SCREEN_WIDTH - al_get_bitmap_width(logo1)) { //Right boundary
            x = SCREEN_WIDTH - al_get_bitmap_width(logo1); //Reset x position to boundary limit
            speedX = -speedX; //Reverse direction of move in X

        }

        if (y < 0) { //Top boundray
            y = zero; //Reset y position to boundary limit
            speedY = -speedY; //Reverse direction of move in Y

        }
        else if (y > SCREEN_HEIGHT - al_get_bitmap_height(logo1)) { //Bottom boundray
            y = SCREEN_HEIGHT - al_get_bitmap_height(logo1); //Reset y position to boundary limit
            speedY = -speedY; //Reverse direction of move in Y

        }

        if (x == zero || x == SCREEN_WIDTH - al_get_bitmap_width(logo1) || y == zero || y == SCREEN_HEIGHT - al_get_bitmap_height(logo1)) {
            numberOfBounces++;
            overallNumberOfBounces++;
            //std::cout << "numberOfBounces " << numberOfBounces << std::endl;
            //std::cout << "overallNumberOfBounces " << overallNumberOfBounces << std::endl;
            
            if (numberOfBounces == numberOfBouncesToCorner) {
                numberOfBounces = -1; //Reset number of bounces between corenr hits
                overallNumberOfBounces += -1; //Assume corner hit as 1 => remove one hit
                endImageChange = 0;
                                                    
            }
        }
        
        if (endImageChange) {
            int currentImageIndex = overallNumberOfBounces % 6;
            if (currentImageIndex == 0) {
                al_draw_bitmap(logo1, x, y, 0);
            }
            else if (currentImageIndex == 1) {
                al_draw_bitmap(logo2, x, y, 0);
            }
            else if (currentImageIndex == 2) {
                al_draw_bitmap(logo3, x, y, 0);
            }
            else if (currentImageIndex == 3) {
                al_draw_bitmap(logo4, x, y, 0);
            }
            else if (currentImageIndex == 4) {
                al_draw_bitmap(logo5, x, y, 0);
            }
            else if (currentImageIndex == 5) {
                al_draw_bitmap(logo6, x, y, 0);
            }
        }
        else {
            al_draw_bitmap(logoFin, x, y, 0);
        }


        //al_draw_bitmap((overallNumberOfBounces % 2 == 0) ? logo1 : logo2, x, y, 0);

        
        //Flip display
        al_flip_display();

    }

    //Free memory
    al_destroy_bitmap(logo1);
    al_destroy_bitmap(logo2);
    al_destroy_display(display);

    return 0;
}









//#include <allegro5/allegro5.h>
//#include <allegro5/allegro_primitives.h>
//#include <allegro5/allegro_image.h>
//#include <iostream>
//#include <vector>
//
//#include "findLCM.h"
//#include <string>
//
//const int SCREEN_WIDTH = 500;
//const int SCREEN_HEIGHT = 300;
//
//int main() {
//    //Initialize Allegro
//    if (!al_init()) {
//        std::cerr << "Failed to initialize Allegro!" << std::endl;
//        return 1;
//    }
//
//    //Initialize module for rendering
//    if (!al_init_primitives_addon()) {
//        std::cerr << "Failed to initialize primitives addon!" << std::endl;
//        return 1;
//    }
//
//    //Initialize module for image input
//    if (!al_init_image_addon()) {
//        std::cerr << "Failed to initialize image addon!" << std::endl;
//        return 1;
//    }
//
//    //Create diplay
//    ALLEGRO_DISPLAY* display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
//    if (!display) {
//        std::cerr << "Failed to create display!" << std::endl;
//        return 1;
//    }
//
//    //Load images
//    ALLEGRO_BITMAP* logo1 = al_load_bitmap("./penguin.png");
//    ALLEGRO_BITMAP* logo2 = al_load_bitmap("./square.png");
//
//    if (!logo1 || !logo2) {
//        std::cerr << "Failed to load images!" << std::endl;
//        al_destroy_display(display);
//        return 1;
//    }
//
//    //Initialize position and speed of movement
//    float x = 0; // SCREEN_WIDTH / 2.0 - al_get_bitmap_width(logo1) / 2.0 + 50;
//    float y = 0; // SCREEN_HEIGHT / 2.0 - al_get_bitmap_height(logo1) / 2.0;
//    float speedX = 0.07;
//    float speedY = 0.07;
//
//    bool logoChanged = false;
//
//    //Calculate prediction of number of noucnes until corner hit
//    int diffScreenLogoH = SCREEN_HEIGHT - al_get_bitmap_height(logo1); //Calculate height difference of screen and image
//    int diffScreenLogoW = SCREEN_WIDTH - al_get_bitmap_width(logo1); //Calculate width difference of screen and image
//
//    std::cout << "Velikost obrazovky: " << SCREEN_HEIGHT << "x" << SCREEN_WIDTH << std::endl;
//    std::cout << "Velikost obrazku1: " << al_get_bitmap_height(logo1) << "x" << al_get_bitmap_width(logo1) << std::endl;
//    std::cout << "Velikost obrazku2: " << al_get_bitmap_height(logo2) << "x" << al_get_bitmap_width(logo2) << std::endl;
//
//
//    int numberOfSteps = FindLCM::calculateLCM(diffScreenLogoH, diffScreenLogoW); //Find Least Common Multiple equal to the number of steps until corner hit
//    int widthOfExtraDomain = numberOfSteps / diffScreenLogoW; //Calculate number of domains (series of reflections) - width (see https://lostmathlessons.blogspot.com/2016/03/bouncing-dvd-logo.html)
//    int heightOfExtraDomain = numberOfSteps / diffScreenLogoH; //Calculate number of domains (series of reflections) - height
//    int numberOfBouncesToCorner = widthOfExtraDomain + heightOfExtraDomain - 1; //Calculate number of bounces until image hits corner
//
//    std::cout << "Pocet odrazu do narazu do rohu: " << numberOfBouncesToCorner << std::endl;
//
//
//    int zero = 0; //Helper zero
//    int numberOfBounces = 0; //Number of bounces in visualisation between corner hits
//    int overallNumberOfbounces = 0; //Overall number of bounces in visualisation
//
//    while (true) {
//        //Set background color
//        al_clear_to_color(al_map_rgb(255, 255, 255));
//
//        //Move image
//        x += speedX;
//        y += speedY;
//
//        //Collision with boundaries
//        if (x < 0) { //Left boundray
//            x = zero; //Reset x position to boundary limit
//            speedX = -speedX; //Reverse direction of move in X
//
//        }
//        else if (x > SCREEN_WIDTH - al_get_bitmap_width(logo1)) { //Right boundary
//            x = SCREEN_WIDTH - al_get_bitmap_width(logo1); //Reset x position to boundary limit
//            speedX = -speedX; //Reverse direction of move in X
//
//        }
//
//        if (y < 0) { //Top boundray
//            y = zero; //Reset y position to boundary limit
//            speedY = -speedY; //Reverse direction of move in Y
//
//        }
//        else if (y > SCREEN_HEIGHT - al_get_bitmap_height(logo1)) { //Bottom boundray
//            y = SCREEN_HEIGHT - al_get_bitmap_height(logo1); //Reset y position to boundary limit
//            speedY = -speedY; //Reverse direction of move in Y
//
//        }
//
//
//        if (x == zero || x == SCREEN_WIDTH - al_get_bitmap_width(logo1) || y == zero || y == SCREEN_HEIGHT - al_get_bitmap_height(logo1)) {
//            numberOfBounces++;
//            overallNumberOfbounces++;
//            if (numberOfBounces == numberOfBouncesToCorner) {
//                numberOfBounces = -1;
//                overallNumberOfbounces += -1;
//                logoChanged = !logoChanged;
//
//            }
//        }
//
//        //al_draw_bitmap(currentImage, x, y, 0);
//
//        if (logoChanged) {
//            al_draw_bitmap(logo2, x, y, 0); //First image
//        }
//        else {
//            al_draw_bitmap(logo1, x, y, 0); //Second image
//        }
//
//        //Flip display
//        al_flip_display();
//    }
//
//    //Free memory
//    al_destroy_bitmap(logo1);
//    al_destroy_bitmap(logo2);
//    al_destroy_display(display);
//
//    return 0;
//}
