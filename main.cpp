#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <fstream>
#include <fftw3.h>

using namespace std;

constexpr int FFT_SIZE = 1024;    // number of samples
constexpr float SAMPLE_FREQUENCY = 48000.0f; // sample frequency

// Function to generate a signal as a sum of harmonics
void generateSignal(const vector<float>& freqs, const vector<float>& amps, vector<complex<float>>& signal) {
    for (int i = 0; i < FFT_SIZE; i++) {
        float t = i / SAMPLE_FREQUENCY;
        float sum = 0.0f;
        // For each harmonic, add amplitude*cos(2pi*f*t)
        for (size_t j = 0; j < freqs.size(); j++) {
            sum += amps[j] * cosf(2.0f * static_cast<float>(M_PI) * freqs[j] * t);
        }
        signal[i] = complex<float>(sum, 0.0f);
    }
}

// Function to compute the spectrum using FFTW
void calculateSpectrum(vector<complex<float>>& signal) {
    fftwf_plan plan = fftwf_plan_dft_1d(FFT_SIZE,
                                        reinterpret_cast<fftwf_complex*>(signal.data()),
                                        reinterpret_cast<fftwf_complex*>(signal.data()),
                                        FFTW_FORWARD, FFTW_ESTIMATE);
    fftwf_execute(plan);
    fftwf_destroy_plan(plan);
}

int main() {
    int numHarmonics;
    cout << "Enter the number of harmonics: ";
    cin >> numHarmonics;

    vector<float> freqs(numHarmonics);
    vector<float> amps(numHarmonics);

    for (int i = 0; i < numHarmonics; i++) {
        cout << "Harmonic " << i+1 << endl;
        cout << "  Frequency (Hz): ";
        cin >> freqs[i];
        cout << "  Amplitude: ";
        cin >> amps[i];
    }

    // Create a vector for the signal (complex values for FFTW plan)
    vector<complex<float>> signal(FFT_SIZE);

    // Generate the signal as a sum of harmonics
    generateSignal(freqs, amps, signal);

    // Write the signal to a text file for plotting
    ofstream signalFile("signal.txt");
    for (int i = 0; i < FFT_SIZE; i++) {
        // Write sample index and value
        signalFile << i << " " << signal[i].real() << "\n";
    }
    signalFile.close();

    // Compute the spectrum (FFT)
    calculateSpectrum(signal);

    // Write the spectrum to a file
    ofstream spectrumFile("spectrum.txt");
    for (int i = 0; i < FFT_SIZE; i++) {
        // Compute the magnitude of the complex number
        float magnitude = abs(signal[i]) / (FFT_SIZE / 2.0f); // normalization
        spectrumFile << i << " " << magnitude << "\n";
    }
    spectrumFile.close();

    cout << "\nSignal data written to file signal.txt, spectrum to file spectrum.txt" << endl;
    return 0;
}