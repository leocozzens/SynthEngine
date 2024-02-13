// Standard C headers
#include <stdio.h>
#include <string.h>
#include <math.h>
// External libraries
#include <portaudio.h>
// Project headers
#include <DC/result.h>

#ifndef M_PI
#define M_PI         (3.14159265)
#endif
#define SAMPLE_RATE         (44100)
#define FRAMES_PER_BUFFER   (512)

#define CHECK(_error) if(_error != paNoError) return (Result) { _error, Pa_GetErrorText(_error) }

#define TABLE_SIZE   (200)
typedef struct {
    float sine[TABLE_SIZE];
    int left_phase;
    int right_phase;
} DualPhase;

static PaDeviceIndex find_device(const char *deviceName, PaDeviceIndex deviceCount);
static void print_device_info(const PaDeviceInfo *targetDevice);
static void set_current_device(PaDeviceIndex index);
static int paOutCallback(const void *inputBuff, void *outBuff,
                        unsigned long framesPerBuffer,
                        const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags,
                        void *userData);


static PaStreamParameters currentDevice;
static DualPhase data;

Result init_player(void) {
    PaError e = Pa_Initialize();
    CHECK(e);

    set_current_device(paNoDevice);
    for(int i = 0; i < TABLE_SIZE; i++)
        data.sine[i] = (float) sin( ((double)i/(double)TABLE_SIZE) * M_PI * 2. );
    data.left_phase = data.right_phase = 0;

    return create_success_result("Succesfully initialized player");
}

Result terminate_player(void) {
    PaError e = Pa_Terminate();
    CHECK(e);
    return create_success_result("Succesfully terminated player");
}

Result set_player_device(const char *deviceName) {
    PaDeviceIndex deviceCount = Pa_GetDeviceCount();
    if(deviceCount < 0) return create_error_result("Failed to get information about audio devices");
    if(deviceCount == 0) return create_error_result("No audio devices found");

    PaDeviceIndex targetDeviceIndex = find_device(deviceName, deviceCount);
    if(targetDeviceIndex == paNoDevice)
        return create_error_result("Could not find audio device");
    
    print_device_info(Pa_GetDeviceInfo(targetDeviceIndex));
    set_current_device(targetDeviceIndex);

    return create_success_result("Set desired device to current");
}

Result player_run(void) {
    PaError e;
    PaStream *oStream;

    e = Pa_OpenStream(
        &oStream,
        NULL,
        &currentDevice,
        SAMPLE_RATE,
        FRAMES_PER_BUFFER,
        paClipOff,
        paOutCallback,
        &data
    );
    CHECK(e);
    e = Pa_StartStream(oStream);
    CHECK(e);
    printf("Play for %d seconds.\n", 1);
    Pa_Sleep(1 * 1000);
    Pa_StopStream(oStream);
    Pa_CloseStream(oStream);
    return create_success_result("Played succesfully");
}

static PaDeviceIndex find_device(const char *deviceName, PaDeviceIndex deviceCount) {
    if(deviceName == NULL)
        return Pa_GetDefaultOutputDevice();

    for(PaDeviceIndex i = 0; i < deviceCount; i++) {
        // printf("Device name - %s\n", Pa_GetDeviceInfo(i)->name);
        if(strcmp(deviceName, Pa_GetDeviceInfo(i)->name) == 0)
            return i;
    }
    return paNoDevice;
}

static void set_current_device(PaDeviceIndex index) {
    memset(&currentDevice, 0, sizeof(currentDevice));
    if(index == paNoDevice) {
        currentDevice.device = paNoDevice;
        return;
    }
    currentDevice.device = index;
    currentDevice.channelCount = 2;
    currentDevice.sampleFormat = paFloat32;
    currentDevice.suggestedLatency = Pa_GetDeviceInfo(index)->defaultLowOutputLatency;
    currentDevice.hostApiSpecificStreamInfo = NULL;
}

static void print_device_info(const PaDeviceInfo *targetDevice) {
    printf("Device name: %s\n"
    "    maxInputChannels: %d\n"
    "    maxOutputChannels: %d\n"
    "    defaultSampleRate: %lf\n",
    targetDevice->name,
    targetDevice->maxInputChannels,
    targetDevice->maxOutputChannels,
    targetDevice->defaultSampleRate);
}

static int paOutCallback(const void *inputBuff, void *outBuff,
                        unsigned long framesPerBuffer,
                        const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags,
                        void *userData) {
    DualPhase *p = userData; 
    float *out = outBuff;
    
    (void) timeInfo;
    (void) statusFlags;
    (void) inputBuff; /* Prevent unused variable warning. */
    
    for(unsigned int i = 0; i < framesPerBuffer; i++) {
        *out++ = p->sine[p->left_phase];  /* left */
        *out++ = p->sine[p->right_phase];  /* right */
        /* Generate simple sawtooth phaser that ranges between -1.0 and 1.0. */
        p->left_phase += 1;
        /* When signal reaches top, drop back down. */
        if( p->left_phase >= TABLE_SIZE ) p->left_phase -= TABLE_SIZE;
        /* higher pitch so we can distinguish left and right. */
        p->right_phase += 3;
        if( p->right_phase >= TABLE_SIZE ) p->right_phase -= TABLE_SIZE;
    }
    return paContinue;
}