#include<SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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



const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 700;
int SPEED = 10;


void drawBars(sf::RenderWindow& window, const vector<int>& array, int x, int y)
{
    window.clear(sf::Color::White);
    int ARRAY_SIZE = array.size();
    int BAR_WIDTH = WINDOW_WIDTH / ARRAY_SIZE;
    for (int i = 0; i < ARRAY_SIZE; ++i)
    {
        sf::RectangleShape bar(sf::Vector2f(BAR_WIDTH, array[i]));
        bar.setPosition(i * BAR_WIDTH, WINDOW_HEIGHT - array[i]);
        if (i == x)
        {

            bar.setFillColor(sf::Color::Red);

        }
        else if (i == y)
        {

            bar.setFillColor(sf::Color::Blue);

        }
        else
        {
            bar.setFillColor(sf::Color::Black);
        }
        window.draw(bar);
    }
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

    cout << BOLD_GREEN; // Reset text style
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
    cout << setw(5) << left << "10" << setw(25) << right << "OddEven SORT" << endl;
    cout << "\n\n\n";



    cout << "Enter Choice : ";
    cin >> ch;
    return ch;

}


void bubbleSort(vector<int> arr, sf::RenderWindow& window)
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

                drawBars(window, arr, j, j + 1);
                sf::sleep(sf::milliseconds(SPEED)); //Adjust the delay for visualization speed
                Beep(1000, 100);
            }
        }

        if (swapped == false)
            break;
    }
}


void selectionSort(vector<int> arr, sf::RenderWindow& window)
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
            Beep(1000, 100);
        drawBars(window, arr, min_idx, i);
        sf::sleep(sf::milliseconds(SPEED)); //Adjust the delay for visualization speed

    }
}


void insertionSort(vector<int> arr, sf::RenderWindow& window)
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

            drawBars(window, arr, j + 1, j);
            sf::sleep(sf::milliseconds(SPEED)); //Adjust the delay for visualization speed

        }
        arr[j + 1] = key;

        drawBars(window, arr, j + 1, i);
        sf::sleep(sf::milliseconds(SPEED)); //Adjust the delay for visualization speed

    }
}



void merge(vector<int>& array, int left, int mid, int right, sf::RenderWindow& window)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1);
    vector<int> R(n2);

    for (int i = 0; i < n1; ++i)
    {
        L[i] = array[left + i];
    }

    for (int j = 0; j < n2; ++j)
    {
        R[j] = array[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            array[k] = L[i];
            ++i;
            drawBars(window, array, i, j);
            sf::sleep(sf::milliseconds(SPEED)); // Adjust the delay for visualization speed
        }
        else
        {
            array[k] = R[j];
            ++j;
            drawBars(window, array, k, j);
            sf::sleep(sf::milliseconds(SPEED)); // Adjust the delay for visualization speed
        }
        ++k;

    }

    while (i < n1)
    {
        array[k] = L[i];
        ++i;
        ++k;

        drawBars(window, array, k, i);
        sf::sleep(sf::milliseconds(SPEED)); // Adjust the delay for visualization speed
    }

    while (j < n2)
    {
        array[k] = R[j];
        ++j;
        ++k;

        drawBars(window, array, k, j);
        sf::sleep(sf::milliseconds(SPEED)); // Adjust the delay for visualization speed
    }
}

void mergeSort(vector<int>& array, int left, int right, sf::RenderWindow& window)
{
    if (left >= right)
    {
        return;
    }
    int mid = left + (right - left) / 2;
    mergeSort(array, left, mid, window);
    mergeSort(array, mid + 1, right, window);
    merge(array, left, mid, right, window);
}




int partition(vector<int>& arr, int low, int high, sf::RenderWindow& window)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
            Beep(1000, 100);

            drawBars(window, arr, i, j);
            sf::sleep(sf::milliseconds(SPEED)); //Adjust the delay for visualization speed

        }
    }
    swap(arr[i + 1], arr[high]);
    Beep(1000, 100);
    drawBars(window, arr, i + 1, high);
    sf::sleep(sf::milliseconds(SPEED));

    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high, sf::RenderWindow& window)
{
    if (low < high) {
        int pi = partition(arr, low, high, window);
        quickSort(arr, low, pi - 1, window);
        quickSort(arr, pi + 1, high, window);
    }
}




void maxHeapify(vector<int>& arr, int n, int i, sf::RenderWindow& window)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        Beep(1000, 100);

        drawBars(window, arr, i, largest);
        sf::sleep(sf::milliseconds(SPEED)); //Adjust the delay for visualization speed



        maxHeapify(arr, n, largest, window);
    }
}

void heapSort(vector<int>& arr, sf::RenderWindow& window)
{
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i, window);

    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        Beep(1000, 100);

        drawBars(window, arr, 0, i);
        sf::sleep(sf::milliseconds(SPEED)); //Adjust the delay for visualization speed


        maxHeapify(arr, i, 0, window);
    }
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
    int max_element = getMax(arr);
    vector<int> count(max_element + 1, 0);

    for (int i = 0; i < arr.size(); ++i)
    {
        count[arr[i]]++;
        Beep(1000, 100);
    }

    int index = 0;
    for (int i = 0; i <= max_element; ++i)
    {
        while (count[i] > 0)
        {
            arr[index++] = i;
            Beep(1000, 100);
            count[i]--;

            drawBars(window, arr, i + 1, i - 1);
            sf::sleep(sf::milliseconds(SPEED)); // Adjust the delay for visualization speed

        }
    }
}


void countingSort(vector<int>& arr, int exp, sf::RenderWindow& window)
{
    vector<int> output(arr.size());
    vector<int> count(10, 0);

    for (int i = 0; i < arr.size(); ++i)
    {
        count[(arr[i] / exp) % 10]++;
    }

    for (int i = 1; i < 10; ++i)
    {
        count[i] += count[i - 1];
    }

    for (int i = arr.size() - 1; i >= 0; --i)
    {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (int i = 0; i < arr.size(); ++i)
    {
        arr[i] = output[i];

        drawBars(window, arr, i + 1, i - 1);
        sf::sleep(sf::milliseconds(SPEED)); // Adjust the delay for visualization speed

    }
}

void radixSort(vector<int>& arr, sf::RenderWindow& window)
{
    int max_element = *std::max_element(arr.begin(), arr.end());

    for (int exp = 1; max_element / exp > 0; exp *= 10)
    {
        countingSort(arr, exp, window);
    }
}




void shellSort(vector<int>& arr, sf::RenderWindow& window)
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


                drawBars(window, arr, j, j - gap);
                sf::sleep(sf::milliseconds(SPEED)); // Adjust the delay for visualization speed

            }

            arr[j] = temp;

            drawBars(window, arr, j, j - gap);
            sf::sleep(sf::milliseconds(SPEED)); // Adjust the delay for visualization speed

        }
    }
}




void oddEvenSort(vector<int>& arr, sf::RenderWindow& window)
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

                drawBars(window, arr, i, i + 1);
                sf::sleep(sf::milliseconds(SPEED)); // Adjust the delay for visualization speed
            }
        }

        for (int i = 0; i <= n - 2; i += 2)
        {
            if (arr[i] > arr[i + 1])
            {
                swap(arr[i], arr[i + 1]);
                sorted = false;

                drawBars(window, arr, i, i + 1);
                sf::sleep(sf::milliseconds(SPEED)); // Adjust the delay for visualization speed
            }
        }
    }
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


            string choice_array[10];
            choice_array[0] = "BUBBLE SORT";
            choice_array[1] = "SELECTION SORT";
            choice_array[2] = "INSERTION SORT";
            choice_array[3] = "MERGE SORT";
            choice_array[4] = "QUICK SORT";
            choice_array[5] = "HEAP SORT";
            choice_array[6] = "COUNT SORT";
            choice_array[7] = "RADIX SORT";
            choice_array[8] = "SHELL SORT";
            choice_array[9] = "ODD_EVEN SORT";


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
                mergeSort(array, 0, number_of_rd_ele - 1, window);

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
                quickSort(array, 0, number_of_rd_ele - 1, window);

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