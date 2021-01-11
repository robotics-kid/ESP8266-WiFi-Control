#include <stdio.h>
#include <math.h>

void colorTemperatureToRGB(int kelvin, float red, float green, float blue) {

    float temp = kelvin / 100;

    if (temp <= 66) {

        red = 255;

        green = temp;
        green = 99.4708025861 * log(green) - 161.1195681661;


        if (temp <= 19) {

            blue = 0;

        }
        else {

            blue = temp - 10;
            blue = 138.5177312231 * log(blue) - 305.0447927307;

        }

    }
    else {

        red = temp - 60;
        red = 329.698727446 * pow(red, -0.1332047592);

        green = temp - 60;
        green = 288.1221695283 * pow(green, -0.0755148492);

        blue = 255;

    }


    red = clamp(red, 0, 255);
    green = clamp(green, 0, 255);
    blue = clamp(blue, 0, 255);

    printf("red: %f \n", red);
    printf("green: %f \n", green);
    printf("blue: %f \n", blue);


}


float clamp(float x, int min, int max) {

    if (x < min) { return min; }
    if (x > max) { return max; }

    return x;

}

int main() {
    double temp = 1500;

    float x = (float)(temp / 1000.0);
    float x2 = x * x;
    float x3 = x2 * x;
    float x4 = x3 * x;
    float x5 = x4 * x;

    float R, G, B = 0;

    // red
    if (temp <= 6600)
        R = 1;
    else
        R = 0.0002889f * x5 - 0.01258f * x4 + 0.2148f * x3 - 1.776f * x2 + 6.907f * x - 8.723f;

    // green
    if (temp <= 6600)
        G = -4.593e-05f * x5 + 0.001424f * x4 - 0.01489f * x3 + 0.0498f * x2 + 0.1669f * x - 0.1653f;
    else
        G = -1.308e-07f * x5 + 1.745e-05f * x4 - 0.0009116f * x3 + 0.02348f * x2 - 0.3048f * x + 2.159f;

    // blue
    if (temp <= 2000)
        B = 0;
    else if (temp < 6600)
        B = 1.764e-05f * x5 + 0.0003575f * x4 - 0.01554f * x3 + 0.1549f * x2 - 0.3682f * x + 0.2386f;
    else
        B = 1;
    
  

    printf("red: %f \n", R*255);
    printf("green: %f \n", G*255);
    printf("blue: %f \n", B*255);

    return 0;
}

