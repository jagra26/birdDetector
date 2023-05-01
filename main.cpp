#include "LibrosaCpp/librosa/librosa.h"
extern "C" {
#include "LibrosaCpp/test/wavreader.h"
}
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    void *h_x = wav_read_open("./audio_0.wav");
    if (h_x == NULL){
        cerr << "open file error";
        return -1;
    }

    int format, channels, sr, bits_per_sample;
    unsigned int data_length;
    int res = wav_get_header(h_x, &format, &channels, &sr, &bits_per_sample,
                             &data_length);
    if (!res) {
        cerr << "get ref header error: " << res << endl;
        return -1;
    }

    /*int samples = data_length * 8 / bits_per_sample;
    std::vector<int16_t> tmp(samples);
    res = wav_read_data(h_x, reinterpret_cast<unsigned char *>(tmp.data()),
                        data_length);
    if (res < 0) {
        cerr << "read wav file error: " << res << endl;
        return -1;
    }
    std::vector<float> x(samples);
    std::transform(tmp.begin(), tmp.end(), x.begin(),
                   [](int16_t a) { return static_cast<float>(a) / 32767.f; });*/
    return 0;
}
