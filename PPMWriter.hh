//
// Created by elff on 10/15/2024.
//

#ifndef PPMWRITER_HH
#define PPMWRITER_HH

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "MFont.hh"
// #include "MUtils.hh"


struct PPMString {
    int rows{};
    int max_line_len{};
    std::string data{};
};

// struct PPMImage {
//     std::vector<unsigned char> data;
//     // Init data vector with width * height and 3 bytes for r/g/b
//     PPMImage(const int width, const int height) {
//         data.resize(width * height * 3);
//     }
// };


// PPMWriter is where everything happens from reading input to calculating the
// image size to writing to the ppmimage vector
class PPMWriter {
public:
    PPMWriter(const std::string& input_file, const std::string& output_file)
    : m_input_file(input_file), m_output_file(output_file) {}

    // Main function to generate a ppm image
    void generate() {
        read_input_file();
        calculate_image_size();
        init_PPMImage();
        write_PPMImage();
        save_PPMImage();
    }
private:
    void read_input_file();
    void calculate_image_size();
    void init_PPMImage();
    void write_PPMImage();
    bool is_printable(char c);
    void save_PPMImage();
    void write_character(std::vector<unsigned char>& image_vec,
        const std::array<int, MFont::CHAR_ARRAY_SIZE>& character,
        int start_x, int start_y);

    int padding {15};
    int m_image_width{400};
    int m_image_height{250};
    std::string m_input_file{"input.txt"};
    std::string m_output_file{"output.ppm"};
    std::string m_header{};
    PPMString m_data{};
    std::vector<unsigned char> m_PPMImage{};
    MFont::Font m_font{};

};


// save_PPMImage takes the ref of a vector and the PPM Header and saves it
// to disk
inline void PPMWriter::save_PPMImage() {
    std::ofstream file(m_output_file, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error opening output file" << std::endl;
        return;
    }
    file.write(m_header.c_str(), m_header.size());

    file.write(reinterpret_cast<const char *>(m_PPMImage.data()), m_PPMImage.size());
    file.close();
}

inline bool PPMWriter::is_printable(const char c) {
    return (c >= 32 && c <= 126);
}

inline void PPMWriter::write_character(
    std::vector<unsigned char> &image_vec,
    const std::array<int, MFont::CHAR_ARRAY_SIZE> &character,
    int start_x,
    int start_y) {
    // Start looping over the Character array data
    for (int y = 0; y < MFont::CHAR_IMAGE_HEIGHT; ++y) {
        for(int x = 0; x < MFont::CHAR_IMAGE_WIDTH; ++x) {
            const int img_x = start_x + x;
            const int img_y = start_y + y;
            const int char_index = y * MFont::CHAR_IMAGE_WIDTH + x;
            const int pixel_index = (img_y * m_image_width + img_x) * 3;

            const unsigned int color = character[char_index];
            image_vec[pixel_index]     = (color >> 16) & 0xFF;  // red
            image_vec[pixel_index + 1] = (color >> 8) & 0xFF;   // green
            image_vec[pixel_index + 2] = color & 0xFF;          // blue
        }
    }
}


// write_PPMImage loops over the entire vector and over the font char array
// then it writes the data from char array into the vector
// TODO: add support for colored text
// TODO: optimize the font loop
inline void PPMWriter::write_PPMImage() {
    int start_x = padding;
    int start_y = padding;

    // Loop over the input string
    for (const auto& c: m_data.data) {
        if (c == '\n') {
            // Go down a row and to the start
            start_x = padding;
            start_y += MFont::CHAR_IMAGE_HEIGHT + 1;
            continue;
        }
        if (is_printable(c)) {
            const auto& char_data = m_font.data[c]; // character array

            write_character(m_PPMImage, char_data, start_x, start_y);

            // Move to the next position to start writing next char
            start_x += MFont::CHAR_IMAGE_WIDTH;

        } else {
            const auto& char_data = m_font.data[1];
            write_character(m_PPMImage, char_data, start_x, start_y);
            start_x += MFont::CHAR_IMAGE_WIDTH;
        }
    }
}

// Init the ppmimage struct
inline void PPMWriter::init_PPMImage() {
    m_PPMImage.resize(m_image_width * m_image_height * 3);
}

// Calculate the image width and height
inline void PPMWriter::calculate_image_size() {
    // Width is <30 px padding> TEXT <30 px padding>
    m_image_width = m_data.max_line_len * MFont::CHAR_IMAGE_WIDTH + (padding*2);
    // Height is how many rows we read from the file + padding up and down
    m_image_height = m_data.rows * MFont::CHAR_IMAGE_HEIGHT + (padding*2);
    // We create the header aswell I guess?
    m_header = "P6\n"
        + std::to_string(m_image_width) + " "
        + std::to_string(m_image_height)+ "\n255\n";
}

// Read the file into PPMString struct
inline void PPMWriter::read_input_file() {
    std::ifstream file;
    file.open(m_input_file);
    std::string line{};
    if (file.is_open()) {
        while (file.good()) {
            std::getline(file, line);
            m_data.data.append(line);
            m_data.data.append("\n");
            m_data.rows++;

            if (m_data.max_line_len < static_cast<int>(line.length())) {
                m_data.max_line_len = static_cast<int>(line.length());
            }

            std::cout << line << std::endl;
        }
    }
    file.close();
}


#endif //PPMWRITER_HH
