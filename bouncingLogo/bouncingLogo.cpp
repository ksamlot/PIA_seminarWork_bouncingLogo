#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "findLCM.h"
#include "terminalBouncing.h"



int SCREEN_WIDTH;
int SCREEN_HEIGHT;


bool check(std::string inputString) {
    return std::all_of(inputString.begin(), inputString.end(), ::isdigit);
}

bool initializeAllegro() {
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
}


int main() {

    initializeAllegro();

    std::cout << "==== Choose visualization mode ====" << std::endl;
    std::cout << "For visualization in terminal paste: terminal" << std::endl;
    std::cout << "For visualization in display screen (using Allegro library) paste: allegro" << std::endl;

    std::string chooseMode;
    std::cin >> chooseMode;

    if (chooseMode == "terminal") { //If user input is "terminal", bouncing logo visualization will be printed to terminal
        std::cout << "You chose terminal" << std::endl;
        Setup();
        for (size_t k = 0; k < 95000; k++)
        {
            Draw();
            Move();
        }
    }

    else if (chooseMode == "allegro") { //If user input is "allegro", bouncing logo visualization will be in display screen
        std::cout << "You chose allegro" << std::endl;
        //Console input dimensions of screen
        std::string input;
        int SCREEN_WIDTH = 800;
        int SCREEN_HEIGHT = 600;

        std::cout << "Enter screen width (recommended 800):" << std::endl;
        std::cin >> input;
        if (check(input)) {
            SCREEN_WIDTH = std::stoi(input);

        }
        else {
            std::cout << "The value " << input << " is not an integer. Using default of 800." << std::endl;
        }

        std::cout << "Enter screen height (recommended 600):" << std::endl;
        std::cin >> input;
        if (check(input)) {
            SCREEN_HEIGHT = std::stoi(input);

        }
        else {
            std::cout << "The value " << input << " is not an integer. Using default of 600." << std::endl;
        }

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
        float speedX = 0.05;
        float speedY = 0.05;

        bool logoChanged = false;

        //Calculate prediction of number of bounces until corner hit
        int diffScreenLogoH = SCREEN_HEIGHT - al_get_bitmap_height(logo1); //Calculate height difference of screen and image
        int diffScreenLogoW = SCREEN_WIDTH - al_get_bitmap_width(logo1); //Calculate width difference of screen and image

        std::cout << "Dimensions of screen: " << SCREEN_WIDTH << "x" << SCREEN_HEIGHT << std::endl;

        int numberOfSteps = FindLCM::calculateLCM(diffScreenLogoH, diffScreenLogoW); //Find Least Common Multiple equal to the number of steps until corner hit
        int widthOfExtraDomain = numberOfSteps / diffScreenLogoW; //Calculate number of domains (series of reflections) - width (see https://lostmathlessons.blogspot.com/2016/03/bouncing-dvd-logo.html)
        int heightOfExtraDomain = numberOfSteps / diffScreenLogoH; //Calculate number of domains (series of reflections) - height
        int numberOfBouncesToCorner = widthOfExtraDomain + heightOfExtraDomain - 1; //Calculate number of bounces until image hits corner

        std::cout << "Number of bounces with walls until corner hit: " << numberOfBouncesToCorner << std::endl;


        int zero = 0; //Helper zero
        int numberOfBounces = 0; //Number of bounces in visualization between corner hits
        int overallNumberOfBounces = 0; //Overall number of bounces in visualization
        int endImageChange = 1; //Switcher for logo change, if =1 images are changing, if =0 only final image is displayed

        while (true) {
            //Set background color
            al_clear_to_color(al_map_rgb(255, 255, 255));

            //Move image
            x += speedX;
            y += speedY;

            //Collision with boundaries
            if (x < 0) { //Left boundary
                x = zero; //Reset x position to boundary limit
                speedX = -speedX; //Reverse direction of move in X

            }
            else if (x > SCREEN_WIDTH - al_get_bitmap_width(logo1)) { //Right boundary
                x = SCREEN_WIDTH - al_get_bitmap_width(logo1); //Reset x position to boundary limit
                speedX = -speedX; //Reverse direction of move in X

            }

            if (y < 0) { //Top boundary
                y = zero; //Reset y position to boundary limit
                speedY = -speedY; //Reverse direction of move in Y

            }
            else if (y > SCREEN_HEIGHT - al_get_bitmap_height(logo1)) { //Bottom boundary
                y = SCREEN_HEIGHT - al_get_bitmap_height(logo1); //Reset y position to boundary limit
                speedY = -speedY; //Reverse direction of move in Y

            }

            if (x == zero || x == SCREEN_WIDTH - al_get_bitmap_width(logo1) || y == zero || y == SCREEN_HEIGHT - al_get_bitmap_height(logo1)) {
                numberOfBounces++;
                overallNumberOfBounces++;
                //std::cout << "numberOfBounces " << numberOfBounces << std::endl;
                //std::cout << "overallNumberOfBounces " << overallNumberOfBounces << std::endl;

                if (numberOfBounces == numberOfBouncesToCorner) {
                    numberOfBounces = -1; //Reset number of bounces between corner hits
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


            //Flip display
            al_flip_display();

        }

        //Free memory
        al_destroy_bitmap(logo1);
        al_destroy_bitmap(logo2);
        al_destroy_display(display);

        return 0;
    }

    else { //if other user input (other than "terminal" or "allegro") exit
        std::cout << "Invalid input" << std::endl;
        return 1;
    }

}
