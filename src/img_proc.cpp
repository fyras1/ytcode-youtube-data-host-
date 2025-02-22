#include <iostream>
#include <vector>
#include <cairo.h>

// Function to create an image from a vector of chars (binary data)
void create_image_from_data(const std::vector<char>& data, int width, int height, const std::string& output_image_path) {
    // Create a Cairo surface to store the image
    cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_RGB24, width, height);
    cairo_t* cr = cairo_create(surface);

    // Set the scale for each tile (8x8 block)
    const int tile_size = 8;

    // Loop over the data and create the tiles
    int byte_index = 0;
    for (int y = 0; y < height; y += tile_size) {
        for (int x = 0; x < width; x += tile_size) {
            if (byte_index < data.size()) {
                // Read the current byte from the data vector
                unsigned char byte = static_cast<unsigned char>(data[byte_index]);

                // Loop over the 8 bits in the byte to create 8 tiles
                for (int bit = 0; bit < 8; ++bit) {
                    // Calculate the position of the tile
                    int tile_x = x + (bit % tile_size);
                    int tile_y = y + (bit / tile_size);

                    // Set color (black or white based on bit value)
                    if (byte & (1 << (7 - bit))) {
                        cairo_set_source_rgb(cr, 0, 0, 0);  // Black
                    } else {
                        cairo_set_source_rgb(cr, 1, 1, 1);  // White
                    }

                    // Draw the tile (a small square)
                    cairo_rectangle(cr, tile_x, tile_y, 32, 16);  // Each tile is 1x1 pixel
                    cairo_fill(cr);
                }
                byte_index++;
            }
        }
    }

    // Write the image to a PNG file
    const char* cstr = output_image_path.c_str();
    cairo_surface_write_to_png(surface, cstr);

    // Clean up
    cairo_destroy(cr);
    cairo_surface_destroy(surface);

    std::cout << "Image saved to: " << output_image_path << std::endl;
}
