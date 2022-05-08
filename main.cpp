#include <complex>
#include <volk/volk.h>
#include "dsp/wav.h"
#include "dsp/fft.h"

int main() {
    dsp::wav::wavReader reader("/home/user/.config/sdrpp/recordings/baseband_1420000000Hz_23-41-53_08-05-2022.wav");
    if(!reader.isHeaderValid()) {
        printf("header is invalid!\n");
        return 1;
    }
    printf("header samplecount: %lu, actual samplecount: %llu, samplerate: %lu, channelcount: %u\n", reader.getHeaderSampleCount(), reader.getActualSampleCount(), reader.getSamplerate(), reader.getChannelCount());
    int fftsize = 4096;

    std::complex<float>* processArray = (std::complex<float>*)malloc(fftsize * sizeof(std::complex<float>));
    float* powerProcessArray = (float*)malloc(fftsize * sizeof(float));
    float* outArray = (float*)calloc(fftsize, sizeof(float));
    dsp::fft::complexPowerSpectrum powerspec(fftsize);
    unsigned int count = 0;
    for(int i = 0; i < (reader.getActualSampleCount() / 2) / fftsize; i+=fftsize) {
        reader.readFloat((float*)processArray, fftsize * 2);
        powerspec.processFFT(processArray, powerProcessArray);
        //volk_32f_accumulator_s32f(outArray, powerProcessArray, fftsize); //for some reason this doesn't work
        for(int j = 0; j < fftsize; j++) {
            outArray[j] += powerProcessArray[j];
        }
        count++;
    }

    for(int i = fftsize / 2; i < fftsize; i++) {
        printf("%f\n", outArray[i] / count);
    }
    for(int i = 0; i < fftsize / 2; i++) {
        printf("%f\n", outArray[i] / count);
    }

    free(processArray);
    free(powerProcessArray);
    free(outArray);
    return 0;
}