# B-Mode-Beamforming

This code is a program that generates a B-mode image containing multiple scanlines from echoes received from an ultrasound transducer. The program includes several classes and functions from different header files, including iostream, ImageDisplay.h, dataBuffer.h, BmodeClass.h, and imageParam.h.

The files 'A4RealRFData.txt' and 'A4ImagRFData.txt' were not uploaded in this repository because they were too big to upload here.

The main function of the code performs the following tasks:
<ol type = 1>
<li> Initialize imaging parameters: A numFrames variable is declared and set to 2. An instance of the imageParam class is created and stored in a pointer parameters, and a message indicating that the parameters have been created is displayed.

<li> Import data into a linked list: Two ifstream objects are created to keep track of the line position in two files, A4ImagRFData.txt and A4RealRFData.txt, containing the imaginary and real parts of the RF data. The program reads the data from these files into two dataBuffer objects, creating a linked list of data buffers. If the files fail to load, an error message is displayed and the program exits.

<li> Beamform data into a linked list: An instance of the BmodeClass class is created and stored in a pointer scanlineHead, which represents the head node of a linked list of scanlines. The BmodeClass objects are created by linking the data buffer nodes in the linked list, and each object beamforms the RF data contained in its corresponding data buffer node into a scanline. The linked list is created by assigning the next attribute of each BmodeClass node to a new BmodeClass object until the number of scanlines reaches the number specified in the imaging parameters.

<li> Aggregate all scanlines into a B-mode image: An array of pointers image2D is created to store the scanlines. The array elements are then pointed to each scanline in the linked list of BmodeClass objects.

<li> Display the linked list: An instance of the ImageDisplay class is created, and the image data is displayed using the display method of the ImageDisplay class. The program then enters a visualization loop, checking for keyboard inputs using the checkInput method of the ImageDisplay class. The display continues until the displayFlag attribute of the ImageDisplay class is set to false.

<li> Destroy all objects: The program deallocates all the memory used by the program, destroying the linked list of data buffers, the linked list of scanlines, and the image data. The exit method of the ImageDisplay class is called to stop the imaging process, and the program ends.
