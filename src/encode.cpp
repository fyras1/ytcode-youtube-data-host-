
#include <iostream>
#include <stdint-gcc.h>
#include <vector>
#include <fstream>
#include <string>
#include <img_pro.hpp>



using namespace std;

#define LOG(...) printf(__VA_ARGS__); printf("\n");


std::vector<char> read_file_to_array(const std::string& file_path);

string srcFile;

void encode_clicked()
{
    vector<char> data = read_file_to_array(srcFile);

        vector<uint8_t> v = {0xAA , 0xFF , 0x55, 0x23};
        std::vector<char> test = static_cast<char>(v);
            // Image dimensions (width, height)
    int width = 64;  // Width in tiles
    int height = 64; // Height in tiles
    
    // Output image path
    std::string output_image_path = "output_image.png";

    // Create the image from data
    create_image_from_data(test, width, height, output_image_path);


}

void upload_clicked()
{


}

void file_clicked(char* filename)
{

        srcFile = string(filename);

}




std::vector<char> read_file_to_array(const std::string& file_path) {
    // Open the file in binary mode
    std::ifstream file(file_path, std::ios::binary);
    
    // Check if the file was opened successfully
    if (!file) {
        std::cerr << "Failed to open file: " << file_path << std::endl;
        return {};
    }
    
    // Get the size of the file
    file.seekg(0, std::ios::end);  // Move to the end of the file
    size_t file_size = file.tellg();  // Get the file size
    file.seekg(0, std::ios::beg);  // Move back to the beginning of the file

    // Create a vector to hold the file contents
    std::vector<char> buffer(file_size);

    // Read the file content into the buffer
    file.read(buffer.data(), file_size);

    // Close the file
    file.close();
    
    return buffer;
}
