#include <iostream>
#include <libserial/SerialPort.h>
#include <libserial/SerialStream.h>
#include <thread>
#include <chrono>
#include <unistd.h>
#include <cstring>

std::thread thread_A, thread_B;
std::chrono::high_resolution_clock::time_point ping_time, pong_time;
LibSerial::SerialPort connection;
std::string device_name;

void talk_function()
{
    //! CHRONO TIMER VARIABLE
    int frequency       = 100;                              // en Hz.
    double time_of_loop = 1000/frequency;                  // en milliseconde.
    std::chrono::high_resolution_clock::time_point last_loop_time = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point x              = std::chrono::high_resolution_clock::now();
    auto next = std::chrono::high_resolution_clock::now();
    //! CHRONO TIMER VARIABLE

    int i = 0;

    while(true)
    {
        //! CHRONO TIMER VARIABLE
        x                          = std::chrono::high_resolution_clock::now();         
        last_loop_time             = x;
        next                       += std::chrono::milliseconds((int)time_of_loop);
        std::this_thread::sleep_until(next);
        //! CHRONO TIMER VARIABLE

        std::string message = "MESSAGE FROM " + device_name;

        if(&connection != NULL)
        {
            std::string msg_id_s = message + " [" + std::to_string(i) + "]\n";
            // int n = msg_id_s.length();
            // char char_array[n + 1];
            // strcpy(char_array, msg_id_s.c_str());
            // // char *msg_id = new char[msg_id_s.length() + 1];
            // // std::strcpy(msg_id, msg_id_s.c_str());
            // std::streamsize taille = 100;
            // char msg[] = "MSG";
            connection.Write(msg_id_s);
            i += 1;
        }
    }
}

void read_function()
{
    std::string reponse;
    char stop = '\n';
    std::streamsize taille = 100;

    while(true)
    {
        if(&connection != NULL)
        {
            connection.ReadLine(reponse, stop);
            std::cout << "[NEW_RECEPTION]> " << reponse << std::endl;
        }
        else
        {
            usleep(500000);
        }
    }
}

int main(int argc, char** argv)
{
    device_name = argv[1];
    connection.Open("/dev/ttyS0");

    connection.SetBaudRate(LibSerial::BaudRate::BAUD_115200);
    connection.SetCharacterSize(LibSerial::CharacterSize::CHAR_SIZE_8);
    connection.SetStopBits(LibSerial::StopBits::STOP_BITS_1);
    connection.SetParity(LibSerial::Parity::PARITY_NONE);

    thread_A = std::thread(&talk_function);
    thread_B = std::thread(&read_function);

    thread_A.join();
    thread_B.join();
}