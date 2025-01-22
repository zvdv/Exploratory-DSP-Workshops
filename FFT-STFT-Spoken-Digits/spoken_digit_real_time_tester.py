import wave
import pyaudio
import librosa
import numpy as np
from tensorflow.keras.models import load_model

class AudioHandler():
    def __init__(self):
        self.FORMAT = pyaudio.paInt32
        self.CHANNELS = 2
        self.RATE = 48000
        self.CHUNK = 1024
        self.record_seconds = 2
        self.audio = None
        self.stream = None
        self.frames = None

    # Starting the Stream
    def start(self):
        print("Recording...")
        self.audio = pyaudio.PyAudio()
        self.stream = self.audio.open(format=self.FORMAT,
                                      channels=self.CHANNELS,
                                      rate=self.RATE,
                                      input=True,
                                      output=False,
                                      frames_per_buffer=self.CHUNK)

        self.frames = []
        for i in range(0, int(self.RATE / self.CHUNK * self.record_seconds)):
            data = self.stream.read(self.CHUNK)
            self.frames.append(data)
        print("Finished...")

    # Stopping the Stream
    def stop(self, i):
        self.stream.close()
        self.audio.terminate()

        waveFile = wave.open("testfile.wav", 'wb')
        waveFile.setnchannels(self.CHANNELS)
        waveFile.setsampwidth(self.audio.get_sample_size(self.FORMAT))
        waveFile.setframerate(self.RATE)
        waveFile.writeframes(b''.join(self.frames))
        waveFile.close()

def Predictor():
    x = []

    linear_data, sr = librosa.load("testfile.wav", sr=8000, mono=True)
    linear_data = linear_data.astype(float)
    absstft = np.abs(librosa.stft(linear_data,n_fft=1024, hop_length=256))
    mean_absstft = np.mean(absstft,axis=1) 
    std_absstft = np.std(absstft, axis=1)
    x_msd = np.hstack([mean_absstft, std_absstft])
    x.append(x_msd) 
    x = np.array(x)

    model = load_model('my_model.keras')
    y_pred = model.predict(x)
    print(y_pred)
    print(y_pred.argmax())

if __name__ == '__main__':
    
    val = 0
    while True:
        inp = input("Enter Y to Record, N to Exit: ")
        if inp == 'y' or inp == 'Y':
            audio = AudioHandler()
            audio.start()
            audio.stop(val)
            Predictor()
            val += 1
        else:
            break
        
    
    