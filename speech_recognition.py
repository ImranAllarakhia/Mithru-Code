import speech_recognition as sr 

def main():

    while True:
    # Initialize the recognizer
        recognizer = sr.Recognizer()
        recognizer.pause_threshold = 0.5

        # Set up the microphone input
        with sr.Microphone() as source:
            print("Listening... Speak now!")

            try:
                # Adjust for ambient noise (optional)
                recognizer.adjust_for_ambient_noise(source)

                # Listen to the microphone input
                audio_data = recognizer.listen(source)

                # Recognize speech using Google Web Speech API
                text = recognizer.recognize_google(audio_data)

                print(f"Transcription: {text}")
            except sr.UnknownValueError:
                print("Could not understand audio. Please try again.")
            except sr.RequestError as e:
                print(f"Error during transcription: {e}")

if __name__ == "__main__":
    main()
