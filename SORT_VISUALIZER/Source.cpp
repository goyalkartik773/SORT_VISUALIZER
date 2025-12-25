#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<cstring>
#include<string>
#include<chrono>
#include<thread>
#include<iomanip>
#include<algorithm>
#include<random>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<cmath>
#include<sstream>
#include<windows.h>



#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD_RED     "\033[1;31m"
#define BOLD_GREEN   "\033[1;32m"
#define BOLD_YELLOW  "\033[1;33m"
#define BOLD_BLUE    "\033[1;34m"
#define BOLD_MAGENTA "\033[1;35m"
#define BOLD_CYAN    "\033[1;36m"
#define BOLD_WHITE   "\033[1;37m"

using namespace std;



// Enhanced Window Configuration
const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;
const int STATS_PANEL_WIDTH = 300;
const int VISUALIZATION_WIDTH = WINDOW_WIDTH - STATS_PANEL_WIDTH;
int SPEED = 10;

// Statistics tracking
struct SortStats {
    long long comparisons = 0;
    long long swaps = 0;
    long long arrayAccesses = 0;
    std::chrono::steady_clock::time_point startTime;
    double elapsedTime = 0.0;
    
    void reset() {
        comparisons = 0;
        swaps = 0;
        arrayAccesses = 0;
        elapsedTime = 0.0;
        startTime = std::chrono::steady_clock::now();
    }
    
    void updateTime() {
        auto now = std::chrono::steady_clock::now();
        elapsedTime = std::chrono::duration<double>(now - startTime).count();
    }
};

SortStats globalStats;

// Color utilities for gradient effects
sf::Color HSVtoRGB(float h, float s, float v) {
    float c = v * s;
    float x = c * (1 - std::abs(fmod(h / 60.0f, 2) - 1));
    float m = v - c;
    
    float r, g, b;
    if (h < 60) { r = c; g = x; b = 0; }
    else if (h < 120) { r = x; g = c; b = 0; }
    else if (h < 180) { r = 0; g = c; b = x; }
    else if (h < 240) { r = 0; g = x; b = c; }
    else if (h < 300) { r = x; g = 0; b = c; }
    else { r = c; g = 0; b = x; }
    
    return sf::Color(
        static_cast<sf::Uint8>((r + m) * 255),
        static_cast<sf::Uint8>((g + m) * 255),
        static_cast<sf::Uint8>((b + m) * 255)
    );
}

// Get color based on value with smooth gradient
sf::Color getGradientColor(int value, int maxValue) {
    float hue = (1.0f - (float)value / maxValue) * 240.0f; // Blue to Red
    return HSVtoRGB(hue, 0.8f, 0.95f);
}


// Enhanced audio feedback with pitch variation
void playTone(int value, int maxValue) {
    int frequency = 200 + (value * 800 / maxValue);
    Beep(frequency, 5);
}

// Enhanced drawing function with professional graphics and SFML features
void drawBars(sf::RenderWindow& window, const vector<int>& array, int highlightIndex1, int highlightIndex2, 
              const std::string& algorithmName, int sortedUpTo = -1) {
    globalStats.updateTime();
    
    // Create gradient background
    sf::VertexArray background(sf::Quads, 4);
    background[0].position = sf::Vector2f(0, 0);
    background[0].color = sf::Color(15, 15, 35);
    background[1].position = sf::Vector2f(VISUALIZATION_WIDTH, 0);
    background[1].color = sf::Color(25, 25, 55);
    background[2].position = sf::Vector2f(VISUALIZATION_WIDTH, WINDOW_HEIGHT);
    background[2].color = sf::Color(35, 15, 45);
    background[3].position = sf::Vector2f(0, WINDOW_HEIGHT);
    background[3].color = sf::Color(25, 15, 35);
    
    window.clear();
    window.draw(background);
    
    int ARRAY_SIZE = array.size();
    float BAR_WIDTH = (float)VISUALIZATION_WIDTH / ARRAY_SIZE;
    int maxValue = *std::max_element(array.begin(), array.end());
    
    // Draw bars with enhanced visuals and shadows
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        float barHeight = ((float)array[i] / maxValue) * (WINDOW_HEIGHT - 150);
        float barX = i * BAR_WIDTH;
        float barY = WINDOW_HEIGHT - barHeight - 60;
        
        // Draw shadow first (offset slightly)
        sf::RectangleShape shadow(sf::Vector2f(BAR_WIDTH - 2, barHeight));
        shadow.setPosition(barX + 3, barY + 3);
        shadow.setFillColor(sf::Color(0, 0, 0, 50));
        window.draw(shadow);
        
        // Main bar with rounded corners effect (using multiple rectangles)
        sf::RectangleShape bar(sf::Vector2f(BAR_WIDTH - 2, barHeight));
        bar.setPosition(barX, barY);
        
        // Color selection with smooth gradients
        if (i == highlightIndex1) {
            bar.setFillColor(sf::Color(255, 50, 50, 255)); // Bright Red - comparing
            // Add glow effect
            sf::RectangleShape glow(sf::Vector2f(BAR_WIDTH + 6, barHeight + 6));
            glow.setPosition(barX - 3, barY - 3);
            glow.setFillColor(sf::Color(255, 100, 100, 80));
            window.draw(glow);
        }
        else if (i == highlightIndex2) {
            bar.setFillColor(sf::Color(50, 150, 255, 255)); // Bright Blue - comparing
            sf::RectangleShape glow(sf::Vector2f(BAR_WIDTH + 6, barHeight + 6));
            glow.setPosition(barX - 3, barY - 3);
            glow.setFillColor(sf::Color(100, 150, 255, 80));
            window.draw(glow);
        }
        else if (sortedUpTo >= 0 && i >= sortedUpTo) {
            bar.setFillColor(sf::Color(50, 255, 100, 255)); // Green - sorted
            // Add subtle glow for sorted elements
            sf::RectangleShape sortedGlow(sf::Vector2f(BAR_WIDTH + 2, barHeight + 2));
            sortedGlow.setPosition(barX - 1, barY - 1);
            sortedGlow.setFillColor(sf::Color(50, 255, 100, 40));
            window.draw(sortedGlow);
        }
        else {
            bar.setFillColor(getGradientColor(array[i], maxValue));
        }
        
        // Add subtle outline
        bar.setOutlineThickness(1);
        bar.setOutlineColor(sf::Color(255, 255, 255, 40));
        
        window.draw(bar);
        
        // Add top highlight for 3D effect
        if (barHeight > 5) {
            sf::RectangleShape highlight(sf::Vector2f(BAR_WIDTH - 4, 3));
            highlight.setPosition(barX + 1, barY + 1);
            highlight.setFillColor(sf::Color(255, 255, 255, 30));
            window.draw(highlight);
        }
    }
    
    // Draw progress bar at bottom
    float progress = 0.0f;
    if (sortedUpTo >= 0) {
        progress = (float)sortedUpTo / ARRAY_SIZE;
    }
    
    // Progress bar background
    sf::RectangleShape progressBg(sf::Vector2f(VISUALIZATION_WIDTH - 40, 10));
    progressBg.setPosition(20, WINDOW_HEIGHT - 30);
    progressBg.setFillColor(sf::Color(50, 50, 70, 150));
    progressBg.setOutlineThickness(1);
    progressBg.setOutlineColor(sf::Color(100, 100, 150, 200));
    window.draw(progressBg);
    
    // Progress bar fill
    if (progress > 0) {
        sf::RectangleShape progressFill(sf::Vector2f((VISUALIZATION_WIDTH - 40) * progress, 10));
        progressFill.setPosition(20, WINDOW_HEIGHT - 30);
        progressFill.setFillColor(sf::Color(50, 255, 100, 200));
        window.draw(progressFill);
    }
    
    // Draw statistics panel with enhanced design
    sf::RectangleShape statsPanel(sf::Vector2f(STATS_PANEL_WIDTH, WINDOW_HEIGHT));
    statsPanel.setPosition(VISUALIZATION_WIDTH, 0);
    statsPanel.setFillColor(sf::Color(20, 20, 40, 250));
    
    // Add subtle border
    statsPanel.setOutlineThickness(2);
    statsPanel.setOutlineColor(sf::Color(100, 100, 150, 100));
    window.draw(statsPanel);
    
    // Create default font (SFML has a built-in default font)
    sf::Font font;
    // Note: For best results, load a custom font file
    // font.loadFromFile("arial.ttf");
    
    // Draw statistics text with proper SFML text rendering
    std::vector<std::pair<std::string, bool>> statsText = {
        {"ALGORITHM", true},
        {algorithmName, false},
        {"", false},
        {"STATISTICS", true},
        {"Comparisons: " + std::to_string(globalStats.comparisons), false},
        {"Swaps: " + std::to_string(globalStats.swaps), false},
        {"Array Access: " + std::to_string(globalStats.arrayAccesses), false},
        {"", false},
        {"Time: " + std::to_string((int)globalStats.elapsedTime) + "s", false},
        {"", false},
        {"ARRAY INFO", true},
        {"Size: " + std::to_string(ARRAY_SIZE), false},
        {"Max Value: " + std::to_string(maxValue), false},
        {"", false},
        {"SPEED", true},
        {std::to_string(SPEED) + " ms", false}
    };
    
    float yPos = 30;
    for (size_t i = 0; i < statsText.size(); ++i) {
        if (statsText[i].first.empty()) {
            yPos += 10;
            continue;
        }
        
        sf::Text text;
        text.setString(statsText[i].first);
        text.setCharacterSize(statsText[i].second ? 22 : 18);
        text.setFillColor(statsText[i].second ? 
                         sf::Color(100, 200, 255) : sf::Color(200, 200, 220));
        text.setPosition(VISUALIZATION_WIDTH + 25, yPos);
        text.setStyle(statsText[i].second ? sf::Text::Bold : sf::Text::Regular);
        
        // Add text shadow for better readability
        sf::Text shadow = text;
        shadow.setPosition(VISUALIZATION_WIDTH + 27, yPos + 2);
        shadow.setFillColor(sf::Color(0, 0, 0, 100));
        window.draw(shadow);
        window.draw(text);
        
        yPos += statsText[i].second ? 40 : 28;
    }
    
    // Draw decorative elements
    // Top accent line
    sf::RectangleShape accentLine(sf::Vector2f(STATS_PANEL_WIDTH - 40, 3));
    accentLine.setPosition(VISUALIZATION_WIDTH + 20, 15);
    accentLine.setFillColor(sf::Color(100, 200, 255, 150));
    window.draw(accentLine);
    
    window.display();
}



class sort_use
{
public:
    vector<string> parameter1;
    vector<string> parameter2;
    vector<string> parameter3;
    string in;
    int ch;
    int lim;
    string temp;
    int set;


    void input()
    {
        cout << "\n\n";
        cout << "MAXIMUM OF THREE PARAMETERS ALLOWED FOR USER TO INPUT" << endl;
        cout << "\n\nEnter number of parameters you want to enter" << endl;
        cin >> lim;
        cout << "\nEnter number of sets you want to enter" << endl;
        cin >> set;
        if (lim == 1)
        {
            int count;
            for (int i = 0; i < set; i++)
            {
                cout << "Enter Set " << i << " value" << endl;
                cin >> temp;
                parameter1.push_back(temp);
            }
        }
        if (lim == 2)
        {
            int count;
            for (int i = 0; i < set; i++)
            {
                count = 1;
                cout << "Enter Set " << i + 1 << " value for parameter " << count << endl;
                count++;
                cin >> temp;
                parameter1.push_back(temp);
                cout << "Enter Set " << i + 1 << " value for parameter " << count << endl;
                count++;
                cin >> temp;
                parameter2.push_back(temp);
            }
        }
        if (lim == 3)
        {
            int count;
            for (int i = 0; i < set; i++)
            {
                count = 1;
                cout << "Enter Set " << i + 1 << " value for parameter " << count << endl;
                count++;
                cin >> temp;
                parameter1.push_back(temp);
                cout << "Enter Set " << i + 1 << " value for parameter " << count << endl;
                count++;
                cin >> temp;
                parameter2.push_back(temp);
                cout << "Enter Set " << i + 1 << " value for parameter " << count << endl;
                count++;
                cin >> temp;
                parameter3.push_back(temp);
            }
        }

    }



    void Sort()
    {
        cout << "Name the parameter you want to sort ?" << endl;
        cin >> ch;
        if (ch == 1)
        {
            int n = parameter1.size();
            int i, j;
            bool swapped;
            for (i = 0; i < n - 1; i++)
            {
                swapped = false;
                for (j = 0; j < n - i - 1; j++)
                {
                    if (parameter1[j] > parameter1[j + 1])
                    {
                        swap(parameter1[j], parameter1[j + 1]);
                        swap(parameter2[j], parameter2[j + 1]);
                        swapped = true;
                    }
                }

                if (swapped == false)
                    break;
            }
        }
        if (ch == 2)
        {
            int n = parameter2.size();
            int i, j;
            bool swapped;
            for (i = 0; i < n - 1; i++)
            {
                swapped = false;
                for (j = 0; j < n - i - 1; j++)
                {
                    if (parameter2[j] > parameter2[j + 1])
                    {
                        swap(parameter1[j], parameter1[j + 1]);
                        swap(parameter2[j], parameter2[j + 1]);
                        swapped = true;
                    }
                }

                if (swapped == false)
                    break;
            }
        }
        if (ch == 3)
        {
            int n = parameter3.size();
            int i, j;
            bool swapped;
            for (i = 0; i < n - 1; i++)
            {
                swapped = false;
                for (j = 0; j < n - i - 1; j++)
                {
                    if (parameter3[j] > parameter3[j + 1])
                    {
                        swap(parameter1[j], parameter1[j + 1]);
                        swap(parameter2[j], parameter2[j + 1]);
                        swap(parameter3[j], parameter3[j + 1]);
                        swapped = true;
                    }
                }

                if (swapped == false)
                    break;
            }
        }
    }

    void display()
    {
        if (lim == 1)
        {
            cout << "\n\n";
            cout << setw(5) << left << "PARAMETER 1" << setw(15) << right << endl;
            cout << "-----------------------------------\n\n";
            for (int i = 0; i < set; i++)
            {
                cout << setw(5) << left << parameter1[i] << endl;
            }
            cout << "\n\n";
        }
        if (lim == 2)
        {
            cout << "\n\n";
            cout << setw(5) << left << "PARAMETER 1" << setw(15) << right << "PARAMETER 2" << endl;
            cout << "-----------------------------------\n\n";
            for (int i = 0; i < set; i++)
            {
                cout << setw(5) << left << parameter1[i] << setw(15) << right << parameter2[i] << endl;
            }
            cout << "\n\n";
        }
        if (lim == 3)
        {
            cout << "\n\n";
            cout << setw(5) << left << "PARAMETER 1" << setw(10) << right << "PARAMETER 2" << setw(15) << right << "PARAMETER 3" << endl;
            cout << "---------------------------------------------------\n\n";
            for (int i = 0; i < set; i++)
            {
                cout << setw(5) << left << parameter1[i] << setw(10) << right << parameter2[i] << setw(15) << right << parameter3[i] << endl;
            }
            cout << "\n\n";
        }
    }






};


void intro_display()
{
    // String for separators and spacing
    string s = "       ";

    // Print the top separator line
    cout << BOLD_YELLOW << "\n";
    for (int i = 0; i < 115; i++)
    {
        cout << "=" << flush;
        this_thread::sleep_for(chrono::milliseconds(10));
    }
    cout << "\n\n";

    // Animated "Welcome" spacing
    for (char c : s)
    {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    cout << "\n\n";

    // ASCII art for title
    const string ascii =
        "\033[1;34m"
        "  __      __       .__                                ___________       \n"
        " /  \\    /  \\ ____ |  |   ____  ____   _____   ____   \\__    ___/___   \n"
        " \\   \\/\\/   // __ \\|  | _/ ___\\/  _ \\ /     \\_/ __ \\    |    | /  _ \\  \n"
        "  \\        /\\  ___/|  |_\\  \\__(  <_> )  Y Y  \\  ___/    |    |(  <_> ) \n"
        "   \\__/\\  /  \\___  >____/\\___  >____/|__|_|  /\\___  >   |____| \\____/  \n"
        "        \\/       \\/          \\/            \\/     \\/                  \n"
       "\033[0m";

    cout << BOLD_MAGENTA << "\n";
    for (char c : ascii)
    {
        cout << c << flush;
        this_thread::sleep_for(chrono::microseconds(999));
    }
    cout << "\n\n";

    // Additional ASCII art
    string ascii_art =
        "\033[1;31m"
        " _____  ___________ _____ ___________ _____ ___________ \n"
        "/  ___||  _  | ___ \\_   _|_   _|  ___|_   _|  ___| ___ \\ \n"
        "\\ `--. | | | | |_/ / | |   | | | |_    | | | |__ | |_/ / \n"
        " `--. \\| | | |    /  | |   | | |  _|   | | |  __||    /  \n"
        "/\\__/ /\\ \\_/ / |\\ \\  | |  _| |_| |    _| |_| |___| |\\ \\ \n"
        "\\____/  \\___/\\_| \\_| \\_/  \\___/\\_|    \\___/\\____/\\_| \\_| \n"
        "                                                         \n"
        "                                                         \n";
        "\033[0m";
    for (char c : ascii_art)
    {
        cout << c << flush;
        this_thread::sleep_for(chrono::microseconds(999));
    }
    cout << "\n\n";

    // Print bottom separator line
    for (int i = 0; i < 115; i++)
    {
        cout << "=" << flush;
        this_thread::sleep_for(chrono::milliseconds(10));
    }
    cout << "\n\n\n";

    // Loading animation
    cout << CYAN;
    for (char c : s)
    {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    cout << "\n";

    s = "Loading . . . .  ";
    for (char c : s)
    {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(250));
    }

    cout << BOLD_GREEN;
}


int mainmenu_display()
{


    int ch;

    cout << "\033[35m";
    cout << "\n\n\n";
    cout << ",-.-.    ,---.    |    ,   .            ,-.-.    ,---.    ,   .    .   ." << endl;
    cout << "| | |    |---|    |    |\\  |            | | |    |---     |\\  |    |   |" << endl;
    cout << "| | |    |   |    |    | \\ |            | | |    |        | \\ |    |   |" << endl;
    cout << "` ' '    `   '    `    `  `'            ` ' '    `---'    `  `'    `---'" << endl;



    string s = "       ";
    for (int i = 0; i < s.length(); i++)
    {
        cout << s.at(i) << flush;
        this_thread::sleep_for(chrono::milliseconds(100));
    }


    cout << "\n\n";
    cout << "\033[1;32m";
    cout << setw(5) << left << "1" << setw(15) << right << "SORT" << endl;
    cout << "-----------------------------------\n";
    cout << "\033[1;33m";
    cout << setw(5) << left << "2" << setw(15) << right << "VISUALIZE" << endl;
    cout << "-----------------------------------\n";
    cout << "\033[1;36m";
    cout << setw(5) << left << "3" << setw(15) << right << "EXIT" << endl;
    cout << "\n\n";

    cout << "Enter Choice : ";
    cin >> ch;
    return ch;



}



int sort_opt_display()
{
    int ch;


    cout << "\n\n";


    cout << "\n\n\n";

    cout << "      SORTING METHOD\n\n\n\n";
    cout << setw(5) << left << "1" << setw(25) << right << "BUBBLE SORT" << endl;
    cout << "-----------------------------------\n";
    cout << setw(5) << left << "2" << setw(25) << right << "SELECTION SORT" << endl;
    cout << "-----------------------------------\n";
    cout << setw(5) << left << "3" << setw(25) << right << "INSERTION SORT" << endl;
    cout << "-----------------------------------\n";
    cout << setw(5) << left << "4" << setw(25) << right << "MERGE SORT" << endl;
    cout << "-----------------------------------\n";
    cout << setw(5) << left << "5" << setw(25) << right << "QUICK SORT" << endl;
    cout << "-----------------------------------\n";
    cout << setw(5) << left << "6" << setw(25) << right << "HEAP SORT" << endl;
    cout << "-----------------------------------\n";
    cout << setw(5) << left << "7" << setw(25) << right << "COUNT SORT" << endl;
    cout << "-----------------------------------\n";
    cout << setw(5) << left << "8" << setw(25) << right << "RADIX SORT" << endl;
    cout << "-----------------------------------\n";
    cout << setw(5) << left << "9" << setw(25) << right << "SHELL SORT" << endl;
    cout << "-----------------------------------\n";
    cout << setw(5) << left << "10" << setw(25) << right << "ODD-EVEN SORT" << endl;
    cout << "-----------------------------------\n";
    cout << BOLD_GREEN << setw(5) << left << "11" << setw(25) << right << "COCKTAIL SORT" << RESET << endl;
    cout << "-----------------------------------\n";
    cout << BOLD_GREEN << setw(5) << left << "12" << setw(25) << right << "COMB SORT" << RESET << endl;
    cout << "-----------------------------------\n";
    cout << BOLD_GREEN << setw(5) << left << "13" << setw(25) << right << "GNOME SORT" << RESET << endl;
    cout << "-----------------------------------\n";
    cout << BOLD_GREEN << setw(5) << left << "14" << setw(25) << right << "TIM SORT" << RESET << endl;
    cout << "\n\n\n";



    cout << "Enter Choice : ";
    cin >> ch;
    return ch;

}


void bubbleSort(vector<int> arr, sf::RenderWindow& window)
{
    globalStats.reset();
    int n = arr.size();
    int i, j;
    bool swapped;
    int maxValue = *std::max_element(arr.begin(), arr.end());
    
    for (i = 0; i < n - 1; i++)
    {
        swapped = false;
        for (j = 0; j < n - i - 1; j++)
        {
            globalStats.comparisons++;
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                globalStats.swaps++;
                swapped = true;

                drawBars(window, arr, j, j + 1, "BUBBLE SORT", n - i - 1);
                playTone(arr[j], maxValue);
                sf::sleep(sf::milliseconds(SPEED));
            }
        }

        if (swapped == false)
            break;
    }
    
    // Final display showing all sorted
    drawBars(window, arr, -1, -1, "BUBBLE SORT", 0);
}


void selectionSort(vector<int> arr, sf::RenderWindow& window)
{
    globalStats.reset();
    int i, j, min_idx;
    int n = arr.size();
    int maxValue = *std::max_element(arr.begin(), arr.end());

    for (i = 0; i < n - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < n; j++)
        {
            globalStats.comparisons++;
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }

        if (min_idx != i) {
            swap(arr[min_idx], arr[i]);
            globalStats.swaps++;
        }
        
        drawBars(window, arr, min_idx, i, "SELECTION SORT", i);
        playTone(arr[i], maxValue);
        sf::sleep(sf::milliseconds(SPEED));
    }
    
    drawBars(window, arr, -1, -1, "SELECTION SORT", 0);
}


void insertionSort(vector<int> arr, sf::RenderWindow& window)
{
    globalStats.reset();
    int n = arr.size();
    int i, key, j;
    int maxValue = *std::max_element(arr.begin(), arr.end());
    
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            globalStats.comparisons++;
            arr[j + 1] = arr[j];
            j = j - 1;
            globalStats.swaps++;

            drawBars(window, arr, j + 1, i, "INSERTION SORT", i);
            playTone(arr[j + 1], maxValue);
            sf::sleep(sf::milliseconds(SPEED));
        }
        arr[j + 1] = key;
    }
    
    drawBars(window, arr, -1, -1, "INSERTION SORT", 0);
}



void merge(vector<int>& array, int left, int mid, int right, sf::RenderWindow& window, int maxValue)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1);
    vector<int> R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = array[left + i];

    for (int j = 0; j < n2; ++j)
        R[j] = array[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        globalStats.comparisons++;
        if (L[i] <= R[j])
        {
            array[k] = L[i];
            ++i;
        }
        else
        {
            array[k] = R[j];
            ++j;
        }
        globalStats.swaps++;
        drawBars(window, array, k, mid, "MERGE SORT");
        playTone(array[k], maxValue);
        sf::sleep(sf::milliseconds(SPEED));
        ++k;
    }

    while (i < n1)
    {
        array[k] = L[i];
        ++i;
        ++k;
        globalStats.swaps++;
    }

    while (j < n2)
    {
        array[k] = R[j];
        ++j;
        ++k;
        globalStats.swaps++;
    }
}

void mergeSort(vector<int>& array, int left, int right, sf::RenderWindow& window, int maxValue)
{
    if (left >= right)
        return;
    
    int mid = left + (right - left) / 2;
    mergeSort(array, left, mid, window, maxValue);
    mergeSort(array, mid + 1, right, window, maxValue);
    merge(array, left, mid, right, window, maxValue);
}

void mergeSortWrapper(vector<int>& array, sf::RenderWindow& window)
{
    globalStats.reset();
    int maxValue = *std::max_element(array.begin(), array.end());
    mergeSort(array, 0, array.size() - 1, window, maxValue);
    drawBars(window, array, -1, -1, "MERGE SORT", 0);
}




int partition(vector<int>& arr, int low, int high, sf::RenderWindow& window, int maxValue)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++)
    {
        globalStats.comparisons++;
        if (arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
            globalStats.swaps++;

            drawBars(window, arr, i, j, "QUICK SORT");
            playTone(arr[i], maxValue);
            sf::sleep(sf::milliseconds(SPEED));
        }
    }
    swap(arr[i + 1], arr[high]);
    globalStats.swaps++;
    drawBars(window, arr, i + 1, high, "QUICK SORT");
    playTone(arr[i + 1], maxValue);
    sf::sleep(sf::milliseconds(SPEED));

    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high, sf::RenderWindow& window, int maxValue)
{
    if (low < high) {
        int pi = partition(arr, low, high, window, maxValue);
        quickSort(arr, low, pi - 1, window, maxValue);
        quickSort(arr, pi + 1, high, window, maxValue);
    }
}

void quickSortWrapper(vector<int>& arr, sf::RenderWindow& window)
{
    globalStats.reset();
    int maxValue = *std::max_element(arr.begin(), arr.end());
    quickSort(arr, 0, arr.size() - 1, window, maxValue);
    drawBars(window, arr, -1, -1, "QUICK SORT", 0);
}




void maxHeapify(vector<int>& arr, int n, int i, sf::RenderWindow& window, int maxValue)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    globalStats.comparisons++;
    if (left < n && arr[left] > arr[largest])
        largest = left;

    globalStats.comparisons++;
    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        globalStats.swaps++;

        drawBars(window, arr, i, largest, "HEAP SORT");
        playTone(arr[i], maxValue);
        sf::sleep(sf::milliseconds(SPEED));

        maxHeapify(arr, n, largest, window, maxValue);
    }
}

void heapSort(vector<int>& arr, sf::RenderWindow& window)
{
    globalStats.reset();
    int n = arr.size();
    int maxValue = *std::max_element(arr.begin(), arr.end());

    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i, window, maxValue);

    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        globalStats.swaps++;

        drawBars(window, arr, 0, i, "HEAP SORT", i);
        playTone(arr[0], maxValue);
        sf::sleep(sf::milliseconds(SPEED));

        maxHeapify(arr, i, 0, window, maxValue);
    }
    
    drawBars(window, arr, -1, -1, "HEAP SORT", 0);
}



int getMax(vector<int>& arr)
{
    int max = arr[0];
    for (size_t i = 1; i < arr.size(); i++)
    {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}

void countSort(vector<int>& arr, sf::RenderWindow& window)
{
    globalStats.reset();
    int max_element = getMax(arr);
    int maxValue = max_element;
    vector<int> count(max_element + 1, 0);

    for (size_t i = 0; i < arr.size(); ++i)
    {
        count[arr[i]]++;
        globalStats.arrayAccesses++;
    }

    int index = 0;
    for (int i = 0; i <= max_element; ++i)
    {
        while (count[i] > 0)
        {
            arr[index++] = i;
            globalStats.swaps++;
            count[i]--;

            drawBars(window, arr, index - 1, index, "COUNT SORT");
            playTone(i, maxValue);
            sf::sleep(sf::milliseconds(SPEED));
        }
    }
    
    drawBars(window, arr, -1, -1, "COUNT SORT", 0);
}


void countingSort(vector<int>& arr, int exp, sf::RenderWindow& window, int maxValue)
{
    int n = (int)arr.size();
    vector<int> output(n);
    vector<int> count(10, 0);

    for (int i = 0; i < n; ++i)
    {
        count[(arr[i] / exp) % 10]++;
        globalStats.arrayAccesses++;
    }

    for (int i = 1; i < 10; ++i)
    {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; --i)
    {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
        globalStats.swaps++;
    }

    for (int i = 0; i < n; ++i)
    {
        arr[i] = output[i];
        globalStats.swaps++;

        drawBars(window, arr, i, (i > 0 ? i - 1 : 0), "RADIX SORT");
        playTone(arr[i], maxValue);
        sf::sleep(sf::milliseconds(SPEED));
    }
}

void radixSort(vector<int>& arr, sf::RenderWindow& window)
{
    globalStats.reset();
    int max_element = *std::max_element(arr.begin(), arr.end());

    for (int exp = 1; max_element / exp > 0; exp *= 10)
    {
        countingSort(arr, exp, window, max_element);
    }
    
    drawBars(window, arr, -1, -1, "RADIX SORT", 0);
}




void shellSort(vector<int>& arr, sf::RenderWindow& window)
{
    globalStats.reset();
    int n = (int)arr.size();
    int maxValue = *std::max_element(arr.begin(), arr.end());

    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            int temp = arr[i];
            int j;

            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
            {
                globalStats.comparisons++;
                arr[j] = arr[j - gap];
                globalStats.swaps++;

                drawBars(window, arr, j, j - gap, "SHELL SORT");
                playTone(arr[j], maxValue);
                sf::sleep(sf::milliseconds(SPEED));
            }

            arr[j] = temp;
            globalStats.swaps++;

            drawBars(window, arr, j, (j >= gap ? j - gap : 0), "SHELL SORT");
            playTone(arr[j], maxValue);
            sf::sleep(sf::milliseconds(SPEED));
        }
    }
    
    drawBars(window, arr, -1, -1, "SHELL SORT", 0);
}




void oddEvenSort(vector<int>& arr, sf::RenderWindow& window)
{
    globalStats.reset();
    int n = (int)arr.size();
    int maxValue = *std::max_element(arr.begin(), arr.end());
    bool sorted = false;

    while (!sorted)
    {
        sorted = true;

        for (int i = 1; i <= n - 2; i += 2)
        {
            globalStats.comparisons++;
            if (arr[i] > arr[i + 1])
            {
                swap(arr[i], arr[i + 1]);
                globalStats.swaps++;
                sorted = false;

                drawBars(window, arr, i, i + 1, "ODD-EVEN SORT");
                playTone(arr[i], maxValue);
                sf::sleep(sf::milliseconds(SPEED));
            }
        }

        for (int i = 0; i <= n - 2; i += 2)
        {
            globalStats.comparisons++;
            if (arr[i] > arr[i + 1])
            {
                swap(arr[i], arr[i + 1]);
                globalStats.swaps++;
                sorted = false;

                drawBars(window, arr, i, i + 1, "ODD-EVEN SORT");
                playTone(arr[i], maxValue);
                sf::sleep(sf::milliseconds(SPEED));
            }
        }
    }
    
    drawBars(window, arr, -1, -1, "ODD-EVEN SORT", 0);
}


// ============ NEW SORTING ALGORITHMS ============

// Cocktail Sort (Bidirectional Bubble Sort)
void cocktailSort(vector<int>& arr, sf::RenderWindow& window)
{
    globalStats.reset();
    int n = arr.size();
    bool swapped = true;
    int start = 0;
    int end = n - 1;
    int maxValue = *std::max_element(arr.begin(), arr.end());

    while (swapped)
    {
        swapped = false;

        // Forward pass
        for (int i = start; i < end; ++i)
        {
            globalStats.comparisons++;
            if (arr[i] > arr[i + 1])
            {
                swap(arr[i], arr[i + 1]);
                globalStats.swaps++;
                swapped = true;

                drawBars(window, arr, i, i + 1, "COCKTAIL SORT");
                playTone(arr[i], maxValue);
                sf::sleep(sf::milliseconds(SPEED));
            }
        }

        if (!swapped)
            break;

        swapped = false;
        --end;

        // Backward pass
        for (int i = end - 1; i >= start; --i)
        {
            globalStats.comparisons++;
            if (arr[i] > arr[i + 1])
            {
                swap(arr[i], arr[i + 1]);
                globalStats.swaps++;
                swapped = true;

                drawBars(window, arr, i, i + 1, "COCKTAIL SORT");
                playTone(arr[i], maxValue);
                sf::sleep(sf::milliseconds(SPEED));
            }
        }

        ++start;
    }
    
    drawBars(window, arr, -1, -1, "COCKTAIL SORT", 0);
}


// Comb Sort (Improved Bubble Sort with Gap)
void combSort(vector<int>& arr, sf::RenderWindow& window)
{
    globalStats.reset();
    int n = arr.size();
    int gap = n;
    const float shrink = 1.3f;
    bool swapped = true;
    int maxValue = *std::max_element(arr.begin(), arr.end());

    while (gap > 1 || swapped)
    {
        gap = (int)(gap / shrink);
        if (gap < 1)
            gap = 1;

        swapped = false;

        for (int i = 0; i + gap < n; ++i)
        {
            globalStats.comparisons++;
            if (arr[i] > arr[i + gap])
            {
                swap(arr[i], arr[i + gap]);
                globalStats.swaps++;
                swapped = true;

                drawBars(window, arr, i, i + gap, "COMB SORT");
                playTone(arr[i], maxValue);
                sf::sleep(sf::milliseconds(SPEED));
            }
        }
    }
    
    drawBars(window, arr, -1, -1, "COMB SORT", 0);
}


// Gnome Sort (Simple comparison-based sort)
void gnomeSort(vector<int>& arr, sf::RenderWindow& window)
{
    globalStats.reset();
    int n = arr.size();
    int index = 0;
    int maxValue = *std::max_element(arr.begin(), arr.end());

    while (index < n)
    {
        if (index == 0)
        {
            index++;
        }
        else
        {
            globalStats.comparisons++;
            if (arr[index] >= arr[index - 1])
            {
                index++;
            }
            else
            {
                swap(arr[index], arr[index - 1]);
                globalStats.swaps++;

                drawBars(window, arr, index, index - 1, "GNOME SORT");
                playTone(arr[index], maxValue);
                sf::sleep(sf::milliseconds(SPEED));

                index--;
            }
        }
    }
    
    drawBars(window, arr, -1, -1, "GNOME SORT", 0);
}


// Tim Sort (Hybrid of Merge Sort and Insertion Sort)
const int RUN = 32;

void insertionSortForTim(vector<int>& arr, int left, int right, sf::RenderWindow& window, int maxValue)
{
    for (int i = left + 1; i <= right; i++)
    {
        int temp = arr[i];
        int j = i - 1;

        while (j >= left && arr[j] > temp)
        {
            globalStats.comparisons++;
            arr[j + 1] = arr[j];
            j--;

            drawBars(window, arr, j + 1, i, "TIM SORT");
            playTone(arr[j + 1], maxValue);
            sf::sleep(sf::milliseconds(SPEED / 2));
        }
        arr[j + 1] = temp;
        globalStats.swaps++;
    }
}

void mergeForTim(vector<int>& arr, int l, int m, int r, sf::RenderWindow& window, int maxValue)
{
    int len1 = m - l + 1, len2 = r - m;
    vector<int> left(len1), right(len2);

    for (int i = 0; i < len1; i++)
        left[i] = arr[l + i];
    for (int i = 0; i < len2; i++)
        right[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;

    while (i < len1 && j < len2)
    {
        globalStats.comparisons++;
        if (left[i] <= right[j])
        {
            arr[k] = left[i];
            i++;
        }
        else
        {
            arr[k] = right[j];
            j++;
        }
        globalStats.swaps++;

        drawBars(window, arr, k, m, "TIM SORT");
        playTone(arr[k], maxValue);
        sf::sleep(sf::milliseconds(SPEED / 2));
        k++;
    }

    while (i < len1)
    {
        arr[k] = left[i];
        k++;
        i++;
        globalStats.swaps++;
    }

    while (j < len2)
    {
        arr[k] = right[j];
        k++;
        j++;
        globalStats.swaps++;
    }
}

void timSort(vector<int>& arr, sf::RenderWindow& window)
{
    globalStats.reset();
    int n = arr.size();
    int maxValue = *std::max_element(arr.begin(), arr.end());

    // Sort individual runs using insertion sort
    for (int i = 0; i < n; i += RUN)
    {
        insertionSortForTim(arr, i, std::min((i + RUN - 1), (n - 1)), window, maxValue);
    }

    // Merge sorted runs
    for (int size = RUN; size < n; size = 2 * size)
    {
        for (int left = 0; left < n; left += 2 * size)
        {
            int mid = left + size - 1;
            int right = std::min((left + 2 * size - 1), (n - 1));

            if (mid < right)
                mergeForTim(arr, left, mid, right, window, maxValue);
        }
    }
    
    drawBars(window, arr, -1, -1, "TIM SORT", 0);
}


void bubbleSort2(vector<int> arr)
{
    int n = arr.size();
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++)
    {
        swapped = false;
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        // If no two elements were swapped
        // by inner loop, then break
        if (swapped == false)
            break;
    }
}


void selectionSort2(vector<int> arr)
{
    int i, j, min_idx;
    int n = arr.size();

    // One by one move boundary of
    // unsorted subarray
    for (i = 0; i < n - 1; i++)
    {

        // Find the minimum element in
        // unsorted array
        min_idx = i;
        for (j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }

        // Swap the found minimum element
        // with the first element
        if (min_idx != i)
            swap(arr[min_idx], arr[i]);
    }
}


void insertionSort2(vector<int> arr)
{
    int n = arr.size();
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        // Move elements of arr[0..i-1],
        // that are greater than key,
        // to one position ahead of their
        // current position
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}



void shellSort2(vector<int>& arr)
{
    int n = arr.size();

    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            int temp = arr[i];
            int j;

            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
            {
                arr[j] = arr[j - gap];
            }

            arr[j] = temp;
        }
    }
}




void oddEvenSort2(vector<int>& arr)
{
    int n = arr.size();
    bool sorted = false;

    while (!sorted)
    {
        sorted = true;

        for (int i = 1; i <= n - 2; i += 2)
        {
            if (arr[i] > arr[i + 1])
            {
                swap(arr[i], arr[i + 1]);
                sorted = false;
            }
        }

        for (int i = 0; i <= n - 2; i += 2)
        {
            if (arr[i] > arr[i + 1])
            {
                swap(arr[i], arr[i + 1]);
                sorted = false;
            }
        }
    }
}


void main_menu()
{
    while (1)
    {
        cout << BOLD_CYAN;
        int usr_choice = mainmenu_display();
        cout << RESET;
        if (usr_choice == 1)
        {
            cout << BOLD_BLUE;
            sort_use obj;
            obj.input();
            obj.Sort();
            obj.display();
            break;
        }
        else if (usr_choice == 2)
        {
            cout << GREEN;
            int sort_choice = sort_opt_display();


            string choice_array[14];
            choice_array[0] = "BUBBLE SORT";
            choice_array[1] = "SELECTION SORT";
            choice_array[2] = "INSERTION SORT";
            choice_array[3] = "MERGE SORT";
            choice_array[4] = "QUICK SORT";
            choice_array[5] = "HEAP SORT";
            choice_array[6] = "COUNT SORT";
            choice_array[7] = "RADIX SORT";
            choice_array[8] = "SHELL SORT";
            choice_array[9] = "ODD-EVEN SORT";
            choice_array[10] = "COCKTAIL SORT";
            choice_array[11] = "COMB SORT";
            choice_array[12] = "GNOME SORT";
            choice_array[13] = "TIM SORT";


            int number_of_rd_ele;
            int range_of_rd_ele;
            cout << "\n\n" << CYAN << "Enter the number of elements you want in the Visualiser (Recommended range 100-200." << RED << " WARNING ! Number cannot be above 200" << CYAN << ")" << RESET << endl;
            cin >> number_of_rd_ele;
            cout << CYAN << "\n\nEnter the range of random elements you want in the Visualiser (Recommended range 100-400." << RED << " WARNING ! Number cannot be above 500" << CYAN << ")" << RESET << endl;
            cin >> range_of_rd_ele;
            cout << CYAN << "\n\nEnter the Speed you want in the Visualiser (Recommended range 10." << RED << " WARNING ! Number should not be above 50" << CYAN << ")" << RESET << endl;
            cin >> SPEED;


            cout << BOLD_BLUE;
            random_device rd;
            uniform_int_distribution<int> d(1, range_of_rd_ele);
            vector<int> array;

            for (int i = 0; i < number_of_rd_ele; i++)
            {
                array.push_back(d(rd));
            }

           /* sf::SoundBuffer buffer;
            if (!buffer.loadFromFile("swap_sound.wav")) {
                cout << "Error loading sound!" << endl;
                return ;
            }
            sf::Sound sound(buffer);*/

            sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), choice_array[sort_choice - 1]);

            switch (sort_choice)
            {
            case 1:
            {
                bubbleSort(array, window);

                sf::Event event;
                while (window.isOpen())
                {
                    while (window.pollEvent(event))
                    {
                        if (event.type == sf::Event::Closed)
                        {
                            window.close();
                        }
                    }
                }
                break;
            }

            case 2:
            {
                selectionSort(array, window);

                sf::Event event;
                while (window.isOpen())
                {
                    while (window.pollEvent(event))
                    {
                        if (event.type == sf::Event::Closed)
                        {
                            window.close();
                        }
                    }
                }
                break;
            }

            case 3:
            {
                insertionSort(array, window);

                sf::Event event;
                while (window.isOpen())
                {
                    while (window.pollEvent(event))
                    {
                        if (event.type == sf::Event::Closed)
                        {
                            window.close();
                        }
                    }
                }
                break;
            }

            case 4:
            {
                mergeSortWrapper(array, window);

                sf::Event event;
                while (window.isOpen())
                {
                    while (window.pollEvent(event))
                    {
                        if (event.type == sf::Event::Closed)
                        {
                            window.close();
                        }
                    }
                }
                break;
            }

            case 5:
            {
                quickSortWrapper(array, window);

                sf::Event event;
                while (window.isOpen())
                {
                    while (window.pollEvent(event))
                    {
                        if (event.type == sf::Event::Closed)
                        {
                            window.close();
                        }
                    }
                }
                break;
            }

            case 6:
            {
                heapSort(array, window);

                sf::Event event;
                while (window.isOpen())
                {
                    while (window.pollEvent(event))
                    {
                        if (event.type == sf::Event::Closed)
                        {
                            window.close();
                        }
                    }
                }
                break;
            }

            case 7:
            {
                countSort(array, window);

                sf::Event event;
                while (window.isOpen())
                {
                    while (window.pollEvent(event))
                    {
                        if (event.type == sf::Event::Closed)
                        {
                            window.close();
                        }
                    }
                }
                break;
            }

            case 8:
            {
                radixSort(array, window);

                sf::Event event;
                while (window.isOpen())
                {
                    while (window.pollEvent(event))
                    {
                        if (event.type == sf::Event::Closed)
                        {
                            window.close();
                        }
                    }
                }
                break;
            }

            case 9:
            {
                shellSort(array, window);

                sf::Event event;
                while (window.isOpen())
                {
                    while (window.pollEvent(event))
                    {
                        if (event.type == sf::Event::Closed)
                        {
                            window.close();
                        }
                    }
                }
                break;
            }

            case 10:
            {
                oddEvenSort(array, window);

                sf::Event event;
                while (window.isOpen())
                {
                    while (window.pollEvent(event))
                    {
                        if (event.type == sf::Event::Closed)
                        {
                            window.close();
                        }
                    }
                }
                break;
            }

            case 11:
            {
                cocktailSort(array, window);

                sf::Event event;
                while (window.isOpen())
                {
                    while (window.pollEvent(event))
                    {
                        if (event.type == sf::Event::Closed)
                        {
                            window.close();
                        }
                    }
                }
                break;
            }

            case 12:
            {
                combSort(array, window);

                sf::Event event;
                while (window.isOpen())
                {
                    while (window.pollEvent(event))
                    {
                        if (event.type == sf::Event::Closed)
                        {
                            window.close();
                        }
                    }
                }
                break;
            }

            case 13:
            {
                gnomeSort(array, window);

                sf::Event event;
                while (window.isOpen())
                {
                    while (window.pollEvent(event))
                    {
                        if (event.type == sf::Event::Closed)
                        {
                            window.close();
                        }
                    }
                }
                break;
            }

            case 14:
            {
                timSort(array, window);

                sf::Event event;
                while (window.isOpen())
                {
                    while (window.pollEvent(event))
                    {
                        if (event.type == sf::Event::Closed)
                        {
                            window.close();
                        }
                    }
                }
                break;
            }

            default:
            {
                cout << "INVALID OUTPUT" << endl;
            }
            }

        }
        else if (usr_choice == 3)
        {
            return;
        }
    }

}


int main()
{
    intro_display();
    main_menu();
    return 0;
}