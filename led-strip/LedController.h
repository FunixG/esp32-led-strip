#define RED_PIN 13
#define GREEN_PIN 12
#define BLUE_PIN 14

#define RED_CHANNEL 0
#define GREEN_CHANNEL 1
#define BLUE_CHANNEL 2

#define FREQUENCY 5000
#define RESOLUTION 8

#define MAX_LUMINOSITY 255

void setupLeds();
void setColor(const unsigned int channel, unsigned int luminosity);
