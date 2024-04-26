# import the opencv library 
import cv2 

# define a video capture object 
vid = cv2.VideoCapture(1) 

# Define the codec using VideoWriter_fourcc and create a VideoWriter object
# We specify output file name "output.avi", codec "MJPG", FPS as 30.0, and frame size as (640, 480)
out = cv2.VideoWriter('output.avi', cv2.VideoWriter_fourcc('M','J','P','G'), 30.0, (640,480))

while(True): 
    # Capture the video frame by frame 
    ret, frame = vid.read() 

    # Write the frame into the file 'output.avi'
    out.write(frame)

    # Display the resulting frame 
    cv2.imshow('frame', frame) 

    # Break the loop when the user closes the window
    if cv2.getWindowProperty('frame', cv2.WND_PROP_VISIBLE) < 1: 
        break

# After the loop release the cap object and writer
vid.release() 
out.release()

# Destroy all the windows 
cv2.destroyAllWindows() 
