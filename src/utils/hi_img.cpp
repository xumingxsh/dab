#include "utils/hi_img.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

namespace {
	const string base64_chars =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789+/";
	string base64_encode(const vector<unsigned char>& data) {
		printf("data size:%ld\n", data.size());
		string encoded;
		int i = 0;
		int j = 0;
		unsigned char char_array_3[3];
		unsigned char char_array_4[4];

		for (const auto& byte : data) {
			char_array_3[i++] = byte;
			if (i == 3) {
				char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
				char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
				char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
				char_array_4[3] = char_array_3[2] & 0x3f;

				for (i = 0; i < 4; i++) {
					encoded += base64_chars[char_array_4[i]];
				}
				i = 0;
			}
		}

		if (i > 0) {
			for (j = i; j < 3; j++) {
				char_array_3[j] = '\0';
			}

			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);

			for (j = 0; j < i + 1; j++) {
				encoded += base64_chars[char_array_4[j]];
			}

			while (i++ < 3) {
				encoded += '=';
			}
		}
		return encoded;
	}
}

namespace dab {
	string png2base64(const string& file_path) {
		ifstream file(file_path, std::ios::binary | std::ios::ate);
		if (!file) {
			return "";
		}

		streamsize size = file.tellg();
		file.seekg(0, std::ios::beg);
		printf("size:%ld\n", size);

		vector<unsigned char> buffer(size);
		if (!file.read(reinterpret_cast<char*>(buffer.data()), size)) {
			return "";
		}

		file.close();
		return base64_encode(buffer);
	}
}